#pragma once

#include "Core.h"
#include "Components/SceneComponent.h"
#if WITH_EDITOR
#include "ActorFactories/ActorFactory.h"
#endif


class UActorFactory;


class FLevelEditorUtils
{
public:
	/**
	* Static: Attempts to place the specified object in the level, returning one or more newly-created actors if successful.
	* IMPORTANT: The placed actor's location must be first set using GEditor->ClickLocation and GEditor->ClickPlane.
	*
	* //JC: Copied from LevelEditorViewport.h/.cpp from UE4.18
	*
	* @param	InLevel			Level in which to drop actor
	* @param	ObjToUse		Asset to attempt to use for an actor to place
	* @param	CursorLocation	Location of the cursor while dropping
	* @param	bSelectActors	If true, select the newly dropped actors (defaults: true)
	* @param	ObjectFlags		The flags to place on the actor when it is spawned
	* @param	FactoryToUse	The preferred actor factory to use (optional)
	*
	* @return	true if the object was successfully used to place an actor; false otherwise
	*/
	static TArray<AActor*> TryPlacingActorFromObject(ULevel* InLevel, UObject* ObjToUse, bool bSelectActors, EObjectFlags ObjectFlags, UActorFactory* FactoryToUse, const FName Name = NAME_None);


	/**
	* Places an actor instance using the factory appropriate for the type of asset
	*
	* @param	AssetObj						the asset that is contained in the d&d operation
	* @param	ObjectFlags						The object flags to place on the actor when it is spawned
	* @param	FactoryToUse					optional actor factory to use to create the actor; if not specified,
	*											the highest priority factory that is valid will be used
	*
	* //JC: Copied from AssetSelectio.h/.cpp from UE4.18
	*
	* @return	the actor that was created by the factory, or NULL if there aren't any factories for this asset (or
	*			the actor couldn't be created for some other reason)
	*/
	static AActor* AddActorForAsset(UObject* AssetObj, bool SelectActor = true, EObjectFlags ObjectFlags = RF_Transactional, UActorFactory* FactoryToUse = NULL, const FName Name = NAME_None);


	/**
	* Places an actor instance using the factory appropriate for the type of asset using the current object selection as the asset
	*
	* @param	ActorClass						The type of actor to create
	* @param	ActorLocation					specify null to position the actor at the mouse location,
	otherwise it will be placed at the origin.
	* @param	ObjectFlags						The object flags to place on the actor when it is spawned
	* @param	FactoryToUse					optional actor factory to use to create the actor; if not specified,
	*											the highest priority factory that is valid will be used
	*
	* //JC: Copied from AssetSelectio.h/.cpp from UE4.18
	*
	* @return	the actor that was created by the factory, or NULL if there aren't any factories for this asset (or
	*			the actor couldn't be created for some other reason)
	*/
	static AActor* AddActorFromSelection(UClass* ActorClass, const FVector* ActorLocation = NULL, bool SelectActor = true, EObjectFlags ObjectFlags = RF_Transactional, UActorFactory* ActorFactory = NULL, const FName Name = NAME_None);


};
