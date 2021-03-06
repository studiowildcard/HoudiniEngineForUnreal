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
*/

#pragma once

#include "HoudiniAssetParameter.h"
#include "HoudiniAssetParameterMultiparm.h"
#include "Tickable.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "HoudiniAssetParameterRampCurveColor.generated.h"


class UCurveBase;
class UHoudiniAssetParameterRamp;
class UHoudiniAssetParameterFloat;
class UHoudiniAssetParameterColor;
class UHoudiniAssetParameterChoice;
class SHoudiniAssetParameterRampCurveEditor;

namespace EHoudiniAssetParameterRampCurveColorEvent
{
	enum Type
	{
		None = 0,
		MoveStop,
		ChangeStopTime,
		ChangeStopColor,
		AddStop,
		RemoveStop
	};
}

UCLASS(BlueprintType)
class HOUDINIENGINERUNTIME_API UHoudiniAssetParameterRampCurveColor : public UCurveLinearColor, public FTickableGameObject
{
	GENERATED_UCLASS_BODY()


public:

	/** Set parent ramp parameter. **/
	void SetParentRampParameter(UHoudiniAssetParameterRamp * InHoudiniAssetParameterRamp);

	/** Return the current type of event. **/
	EHoudiniAssetParameterRampCurveColorEvent::Type GetColorEvent() const;

	/** Reset the current type of event. **/
	void ResetColorEvent();


	/** FCurveOwnerInterface methods. **/
public:

#if WITH_EDITOR

	//JC: does this need a replacement? isn't available in the base class in this UE4 version
	//virtual void OnCurveChanged(const TArray< FRichCurveEditInfo > & ChangedCurveEditInfos) override;

#endif

	/** UObject methods. **/
public:

	virtual bool Modify(bool bAlwaysMarkDirty);

	/** FTickableGameObject methods. **/
public:

	virtual bool IsTickableInEditor() const;
	virtual bool IsTickableWhenPaused() const;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;

protected:

	/** Attempt to map current editor transaction type to curve transactions. **/
	EHoudiniAssetParameterRampCurveColorEvent::Type GetEditorCurveTransaction() const;

protected:

	/** Parent ramp parameter. **/
	TWeakObjectPtr<UHoudiniAssetParameterRamp> HoudiniAssetParameterRamp;

	/** Current event. **/
	EHoudiniAssetParameterRampCurveColorEvent::Type ColorEvent;
};
