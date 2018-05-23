/*
* Copyright (c) <2017> Side Effects Software Inc.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/


#include "HoudiniApi.h"
#include "HoudiniAssetParameterRampCurveColor.h"
#include "HoudiniEngineRuntimePrivatePCH.h"
#include "HoudiniAssetParameterColor.h"
#include "HoudiniAssetParameterChoice.h"
#include "HoudiniAssetParameterFloat.h"
#include "HoudiniAssetComponent.h"
#include "Curves/CurveBase.h"
#include "SlateApplication.h"


UHoudiniAssetParameterRampCurveColor::UHoudiniAssetParameterRampCurveColor( const class FPostConstructInitializeProperties& PCIP )
    : Super( PCIP )
    , ColorEvent( EHoudiniAssetParameterRampCurveColorEvent::None )
{}



#if WITH_EDITOR

/*
void
UHoudiniAssetParameterRampCurveColor::OnCurveChanged(const TArray< FRichCurveEditInfo > & ChangedCurveEditInfos)
{
	Super::OnCurveChanged(ChangedCurveEditInfos);

	if (HoudiniAssetParameterRamp.IsValid())
		HoudiniAssetParameterRamp->OnCurveColorChanged(this);

	// FIXME
	// Unfortunately this will not work as SColorGradientEditor is missing OnCurveChange callback calls.
	// This is most likely UE4 bug.
}
*/

#endif

bool
UHoudiniAssetParameterRampCurveColor::Modify(bool bAlwaysMarkDirty)
{
	ColorEvent = GetEditorCurveTransaction();
	return Super::Modify(bAlwaysMarkDirty);
}

EHoudiniAssetParameterRampCurveColorEvent::Type
UHoudiniAssetParameterRampCurveColor::GetEditorCurveTransaction() const
{
	EHoudiniAssetParameterRampCurveColorEvent::Type TransactionType = EHoudiniAssetParameterRampCurveColorEvent::None;

#if WITH_EDITOR

	if (GEditor)
	{
		const FString & TransactionName = GEditor->GetTransactionName().ToString();

		if (TransactionName.Equals(TEXT("Move Gradient Stop")))
			TransactionType = EHoudiniAssetParameterRampCurveColorEvent::MoveStop;
		else if (TransactionName.Equals(TEXT("Add Gradient Stop")))
			TransactionType = EHoudiniAssetParameterRampCurveColorEvent::AddStop;
		else if (TransactionName.Equals(TEXT("Delete Gradient Stop")))
			TransactionType = EHoudiniAssetParameterRampCurveColorEvent::RemoveStop;
		else if (TransactionName.Equals(TEXT("Change Gradient Stop Time")))
			TransactionType = EHoudiniAssetParameterRampCurveColorEvent::ChangeStopTime;
		else if (TransactionName.Equals(TEXT("Change Gradient Stop Color")))
			TransactionType = EHoudiniAssetParameterRampCurveColorEvent::ChangeStopColor;
		else
			TransactionType = EHoudiniAssetParameterRampCurveColorEvent::None;
	}
	else
	{
		TransactionType = EHoudiniAssetParameterRampCurveColorEvent::None;
	}

#endif

	return TransactionType;
}

void
UHoudiniAssetParameterRampCurveColor::SetParentRampParameter(UHoudiniAssetParameterRamp * InHoudiniAssetParameterRamp)
{
	HoudiniAssetParameterRamp = InHoudiniAssetParameterRamp;
}

EHoudiniAssetParameterRampCurveColorEvent::Type
UHoudiniAssetParameterRampCurveColor::GetColorEvent() const
{
	return ColorEvent;
}

void
UHoudiniAssetParameterRampCurveColor::ResetColorEvent()
{
	ColorEvent = EHoudiniAssetParameterRampCurveColorEvent::None;
}

bool
UHoudiniAssetParameterRampCurveColor::IsTickableInEditor() const
{
	return true;
}

bool
UHoudiniAssetParameterRampCurveColor::IsTickableWhenPaused() const
{
	return true;
}

void
UHoudiniAssetParameterRampCurveColor::Tick(float DeltaTime)
{
	if (HoudiniAssetParameterRamp.IsValid())
	{

#if WITH_EDITOR

		if (GEditor && !GEditor->IsTransactionActive())
		{
			switch (ColorEvent)
			{
			case EHoudiniAssetParameterRampCurveColorEvent::ChangeStopTime:
			case EHoudiniAssetParameterRampCurveColorEvent::ChangeStopColor:
			{
				// If color picker is open, we need to wait until it is closed.
				TSharedPtr< SWindow > ActiveTopLevelWindow = FSlateApplication::Get().GetActiveTopLevelWindow();
				if (ActiveTopLevelWindow.IsValid())
				{
					const FString& ActiveTopLevelWindowTitle = ActiveTopLevelWindow->GetTitle().ToString();
					if (ActiveTopLevelWindowTitle.Equals(TEXT("Color Picker")))
						return;
				}
			}

			default:
			{
				break;
			}
			}
		}

		// Notify parent ramp parameter that color has changed.
		HoudiniAssetParameterRamp->OnCurveColorChanged(this);

#endif

	}
	else
	{
		// If we are ticking for whatever reason, stop.
		ResetColorEvent();
	}
}

TStatId
UHoudiniAssetParameterRampCurveColor::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UHoudiniAssetParameterRampCurveColor, STATGROUP_Tickables);
}

bool
UHoudiniAssetParameterRampCurveColor::IsTickable() const
{
#if WITH_EDITOR

	if (GEditor)
	{
		return ColorEvent != EHoudiniAssetParameterRampCurveColorEvent::None;
	}

#endif

	return false;
}
