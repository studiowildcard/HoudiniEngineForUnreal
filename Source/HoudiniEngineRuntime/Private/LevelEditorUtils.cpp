#include "HoudiniApi.h"
#include "GameFramework/Actor.h"

#if WITH_EDITOR
#include "Editor.h"
#include "Editor/UnrealEd/Private/Editor/ActorPositioning.h"
#include "Editor/UnrealEd/Public/SnappingUtils.h"
#include "Editor/UnrealEd/Public/AssetSelection.h"
#include "Runtime/Engine/Public/LevelUtils.h"
#include "Framework/Notifications/NotificationManager.h"
#endif

#include "HoudiniEngineRuntime/Private/LevelEditorUtils.h"


/**
* Creates an actor using the specified factory.
*
* Does nothing if ActorClass is NULL.
*/
static AActor* PrivateAddActor(UObject* Asset, UActorFactory* Factory, bool SelectActor = true, EObjectFlags ObjectFlags = RF_Transactional, const FName Name = NAME_None)
{
#if WITH_EDITOR
	if (!Factory)
	{
		return nullptr;
	}

	AActor* Actor = NULL;
	AActor* NewActorTemplate = Factory->GetDefaultActor(Asset);
	if (!NewActorTemplate)
	{
		return nullptr;
	}

	UWorld* OldWorld = nullptr;

	// The play world needs to be selected if it exists
	if (GIsEditor && GEditor->PlayWorld && !GIsPlayInEditorWorld)
	{
		OldWorld = SetPlayInEditorWorld(GEditor->PlayWorld);
	}

	// For Brushes/Volumes, use the default brush as the template rather than the factory default actor
	if (NewActorTemplate->IsA(ABrush::StaticClass()) && GWorld->GetDefaultBrush() != nullptr)
	{
		NewActorTemplate = GWorld->GetDefaultBrush();
	}

	const FSnappedPositioningData PositioningData = FSnappedPositioningData(GCurrentLevelEditingViewportClient, GEditor->ClickLocation, GEditor->ClickPlane)
		.UseFactory(Factory)
		.UsePlacementExtent(NewActorTemplate->GetPlacementExtent());

	FTransform ActorTransform = FActorPositioning::GetSnappedSurfaceAlignedTransform(PositioningData);

	if (GetDefault<ULevelEditorViewportSettings>()->SnapToSurface.bEnabled)
	{
		// HACK: If we are aligning rotation to surfaces, we have to factor in the inverse of the actor transform so that the resulting transform after SpawnActor is correct.

		if (auto* RootComponent = NewActorTemplate->GetRootComponent())
		{
			RootComponent->UpdateComponentToWorld();
		}
		ActorTransform = NewActorTemplate->GetTransform().Inverse() * ActorTransform;
	}

	// Do not fade snapping indicators over time if the viewport is not realtime
	bool bClearImmediately = !GCurrentLevelEditingViewportClient || !GCurrentLevelEditingViewportClient->IsRealtime();
	FSnappingUtils::ClearSnappingHelpers(bClearImmediately);

	ULevel* DesiredLevel = GWorld->GetCurrentLevel();

	// Don't spawn the actor if the current level is locked.
	if (FLevelUtils::IsLevelLocked(DesiredLevel))
	{
		FNotificationInfo Info(NSLOCTEXT("UnrealEd", "Error_OperationDisallowedOnLockedLevel", "The requested operation could not be completed because the level is locked."));
		Info.ExpireDuration = 3.0f;
		FSlateNotificationManager::Get().AddNotification(Info);
	}
	else
	{
		FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "CreateActor", "Create Actor"), (ObjectFlags & RF_Transactional) != 0);

		// Create the actor.
		Actor = Factory->CreateActor(Asset, DesiredLevel, ActorTransform, ObjectFlags, Name);
		if (Actor)
		{
			if (SelectActor)
			{
				GEditor->SelectNone(false, true);
				GEditor->SelectActor(Actor, true, true);
			}

			Actor->InvalidateLightingCache();
			Actor->PostEditChange();
		}

		GEditor->RedrawLevelEditingViewports();
	}

	if (Actor)
	{
		Actor->MarkPackageDirty();
		ULevel::LevelDirtiedEvent.Broadcast();
	}

	// Restore the old world if there was one
	if (OldWorld)
	{
		RestoreEditorWorld(OldWorld);
	}

	return Actor;
#endif // WITH_EDITOR
	return nullptr;
}


TArray<AActor*> FLevelEditorUtils::TryPlacingActorFromObject(ULevel* InLevel, UObject* ObjToUse, bool bSelectActors, EObjectFlags ObjectFlags, UActorFactory* FactoryToUse, const FName Name)
{
	TArray<AActor*> PlacedActors;

#if WITH_EDITOR

	UClass* ObjectClass = Cast<UClass>(ObjToUse);

	if (ObjectClass == NULL)
	{
		ObjectClass = ObjToUse->GetClass();
		check(ObjectClass);
	}

	AActor* PlacedActor = NULL;
	if (ObjectClass->IsChildOf(AActor::StaticClass()))
	{
		//Attempting to drop a UClass object
		UActorFactory* ActorFactory = FactoryToUse;
		if (ActorFactory == NULL)
		{
			ActorFactory = GEditor->FindActorFactoryForActorClass(ObjectClass);
		}

		if (ActorFactory != NULL)
		{
			PlacedActor = FActorFactoryAssetProxy::AddActorFromSelection(ObjectClass, NULL, bSelectActors, ObjectFlags, ActorFactory, Name);
		}

		if (PlacedActor == NULL && ActorFactory != NULL)
		{
			PlacedActor = FActorFactoryAssetProxy::AddActorForAsset(ObjToUse, bSelectActors, ObjectFlags, ActorFactory, Name);
		}

		if (PlacedActor == NULL && !ObjectClass->HasAnyClassFlags(CLASS_NotPlaceable | CLASS_Abstract))
		{
			// If no actor factory was found or failed, add the actor directly.
			const FTransform ActorTransform = FActorPositioning::GetCurrentViewportPlacementTransform(*ObjectClass->GetDefaultObject<AActor>());
			PlacedActor = GEditor->AddActor(InLevel, ObjectClass, ActorTransform, /*bSilent=*/false, ObjectFlags);
		}

		if (PlacedActor != NULL)
		{
			FVector Collision = ObjectClass->GetDefaultObject<AActor>()->GetPlacementExtent();
			PlacedActors.Add(PlacedActor);
		}
	}

	if ((NULL == PlacedActor) && ObjToUse->IsA(UExportTextContainer::StaticClass()))
	{
		UExportTextContainer* ExportContainer = CastChecked<UExportTextContainer>(ObjToUse);
		const TArray<AActor*> NewActors = GEditor->AddExportTextActors(ExportContainer->ExportText, /*bSilent*/false, ObjectFlags);
		PlacedActors.Append(NewActors);
	}
	else if ((NULL == PlacedActor) && ObjToUse->IsA(UBrushBuilder::StaticClass()))
	{
		UBrushBuilder* BrushBuilder = CastChecked<UBrushBuilder>(ObjToUse);
		UWorld* World = InLevel->OwningWorld;
		BrushBuilder->Build(World);

		ABrush* DefaultBrush = World->GetDefaultBrush();
		if (DefaultBrush != NULL)
		{
			FVector ActorLoc = GEditor->ClickLocation + GEditor->ClickPlane * (FVector::BoxPushOut(GEditor->ClickPlane, DefaultBrush->GetPlacementExtent()));
			FSnappingUtils::SnapPointToGrid(ActorLoc, FVector::ZeroVector);

			DefaultBrush->SetActorLocation(ActorLoc);
			PlacedActor = DefaultBrush;
			PlacedActors.Add(DefaultBrush);
		}
	}
	else if (NULL == PlacedActor)
	{
		bool bPlace = true;
		if (ObjectClass->IsChildOf(UBlueprint::StaticClass()))
		{
			UBlueprint* BlueprintObj = StaticCast<UBlueprint*>(ObjToUse);
			bPlace = BlueprintObj->GeneratedClass != NULL;
			if (bPlace)
			{
				check(BlueprintObj->ParentClass == BlueprintObj->GeneratedClass->GetSuperClass());
				if (BlueprintObj->GeneratedClass->HasAnyClassFlags(CLASS_NotPlaceable | CLASS_Abstract))
				{
					bPlace = false;
				}
			}
		}

		if (bPlace)
		{
			PlacedActor = FActorFactoryAssetProxy::AddActorForAsset(ObjToUse, bSelectActors, ObjectFlags, FactoryToUse, Name);
			if (PlacedActor != NULL)
			{
				PlacedActors.Add(PlacedActor);
				PlacedActor->PostEditMove(true);
			}
		}
	}

#endif // WITH_EDITOR

	return PlacedActors;
}

AActor* FLevelEditorUtils::AddActorForAsset(UObject* AssetObj, bool SelectActor, EObjectFlags ObjectFlags, UActorFactory* FactoryToUse /*= NULL*/, const FName Name)
{
	AActor* Result = NULL;

#if WITH_EDITOR

	const FAssetData AssetData(AssetObj);
	FText UnusedErrorMessage;
	if (AssetObj != NULL)
	{
		// If a specific factory has been provided, verify its validity and then use it to create the actor
		if (FactoryToUse)
		{
			if (FactoryToUse->CanCreateActorFrom(AssetData, UnusedErrorMessage))
			{
				Result = PrivateAddActor(AssetObj, FactoryToUse, SelectActor, ObjectFlags, Name);
			}
		}
		// If no specific factory has been provided, find the highest priority one that is valid for the asset and use
		// it to create the actor
		else
		{
			const TArray<UActorFactory*>& ActorFactories = GEditor->ActorFactories;
			for (int32 FactoryIdx = 0; FactoryIdx < ActorFactories.Num(); FactoryIdx++)
			{
				UActorFactory* ActorFactory = ActorFactories[FactoryIdx];

				// Check if the actor can be created using this factory, making sure to check for an asset to be assigned from the selector
				if (ActorFactory->CanCreateActorFrom(AssetData, UnusedErrorMessage))
				{
					Result = PrivateAddActor(AssetObj, ActorFactory, SelectActor, ObjectFlags, Name);
					if (Result != NULL)
					{
						break;
					}
				}
			}
		}
	}

#endif // WITH_EDITOR

	return Result;
}

AActor* FLevelEditorUtils::AddActorFromSelection(UClass* ActorClass, const FVector* ActorLocation, bool SelectActor, EObjectFlags ObjectFlags, UActorFactory* ActorFactory, const FName Name)
{
#if WITH_EDITOR
	check(ActorClass != NULL);

	if (!ActorFactory)
	{
		// Look for an actor factory capable of creating actors of the actors type.
		ActorFactory = GEditor->FindActorFactoryForActorClass(ActorClass);
	}

	AActor* Result = NULL;
	FText ErrorMessage;

	if (ActorFactory)
	{
		UObject* TargetObject = GEditor->GetSelectedObjects()->GetTop<UObject>();

		if (TargetObject && ActorFactory->CanCreateActorFrom(FAssetData(TargetObject), ErrorMessage))
		{
			// Attempt to add the actor
			Result = PrivateAddActor(TargetObject, ActorFactory, SelectActor, ObjectFlags);
		}
	}

	return Result;

#endif // WITH_EDITOR

	return nullptr;
}

