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
#include "HoudiniAssetParameterRamp.h"
#include "HoudiniEngineRuntimePrivatePCH.h"
#include "HoudiniAssetParameterColor.h"
#include "HoudiniAssetParameterChoice.h"
#include "HoudiniAssetParameterFloat.h"
#include "HoudiniAssetComponent.h"
#include "Curves/CurveBase.h"
#include "SlateApplication.h"

const EHoudiniAssetParameterRampKeyInterpolation::Type
UHoudiniAssetParameterRamp::DefaultSplineInterpolation = EHoudiniAssetParameterRampKeyInterpolation::MonotoneCubic;

const EHoudiniAssetParameterRampKeyInterpolation::Type
UHoudiniAssetParameterRamp::DefaultUnknownInterpolation = EHoudiniAssetParameterRampKeyInterpolation::Linear;

UHoudiniAssetParameterRamp::UHoudiniAssetParameterRamp(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
    , HoudiniAssetParameterRampCurveFloat( nullptr )
    , HoudiniAssetParameterRampCurveColor( nullptr )
    , bIsFloatRamp( true )
    , bIsCurveChanged( false )
    , bIsCurveUploadRequired( false )
{}

UHoudiniAssetParameter * 
UHoudiniAssetParameterRamp::Duplicate( UObject* InOuter )
{
    if( UHoudiniAssetParameterRamp* NewParm = Cast<UHoudiniAssetParameterRamp>( Super::Duplicate( InOuter ) ) )
    {
        // The duplicate has had PostLoad called, so we need to fix ownership of the curve subobjects
        if( HoudiniAssetParameterRampCurveColor )
        {
            NewParm->HoudiniAssetParameterRampCurveColor = DuplicateObject<UHoudiniAssetParameterRampCurveColor>( HoudiniAssetParameterRampCurveColor, InOuter );
            NewParm->HoudiniAssetParameterRampCurveColor->SetParentRampParameter( NewParm );
            HoudiniAssetParameterRampCurveColor->SetParentRampParameter( this );
        }

        if( HoudiniAssetParameterRampCurveFloat )
        {
            NewParm->HoudiniAssetParameterRampCurveFloat = DuplicateObject<UHoudiniAssetParameterRampCurveFloat>( HoudiniAssetParameterRampCurveFloat, InOuter );
            NewParm->HoudiniAssetParameterRampCurveFloat->SetParentRampParameter( NewParm );
            HoudiniAssetParameterRampCurveFloat->SetParentRampParameter( this );
        }
        return NewParm;
    }
    return nullptr;
}

UHoudiniAssetParameterRamp *
UHoudiniAssetParameterRamp::Create(
    UObject * InPrimaryObject,
    UHoudiniAssetParameter * InParentParameter,
    HAPI_NodeId InNodeId, const HAPI_ParmInfo & ParmInfo )
{
    UObject * Outer = InPrimaryObject;
    if ( !Outer )
    {
        Outer = InParentParameter;
        if ( !Outer )
        {
            // Must have either component or parent not null.
            check( false );
        }
    }

	UHoudiniAssetParameterRamp * HoudiniAssetParameterRamp = ConstructObject< UHoudiniAssetParameterRamp >(
		UHoudiniAssetParameterRamp::StaticClass(), Outer, NAME_None, RF_Public | RF_Transactional);

    HoudiniAssetParameterRamp->CreateParameter( InPrimaryObject, InParentParameter, InNodeId, ParmInfo );

    return HoudiniAssetParameterRamp;
}

bool
UHoudiniAssetParameterRamp::CreateParameter(
    UObject * InPrimaryObject,
    UHoudiniAssetParameter * InParentParameter,
    HAPI_NodeId InNodeId, const HAPI_ParmInfo & ParmInfo )
{
    if ( !Super::CreateParameter( InPrimaryObject, InParentParameter, InNodeId, ParmInfo ) )
        return false;

    if ( ParmInfo.rampType == HAPI_RAMPTYPE_FLOAT )
    {
        bIsFloatRamp = true;
    }
    else if ( ParmInfo.rampType == HAPI_RAMPTYPE_COLOR )
    {
        bIsFloatRamp = false;
    }
    else
    {
        return false;
    }

    return true;
}

void
UHoudiniAssetParameterRamp::NotifyChildParametersCreated()
{
    if ( bIsCurveUploadRequired )
    {
        bIsCurveChanged = true;
        OnCurveEditingFinished();
        bIsCurveUploadRequired = false;
    }
    else
    {
        GenerateCurvePoints();

#if WITH_EDITOR

        if ( HoudiniAssetParameterRampCurveColor )
            OnParamStateChanged();

#endif

    }
}

void
UHoudiniAssetParameterRamp::OnCurveFloatChanged( UHoudiniAssetParameterRampCurveFloat * CurveFloat )
{
    if ( !CurveFloat )
        return;

    FRichCurve & RichCurve = CurveFloat->FloatCurve;

    if ( RichCurve.GetNumKeys() < MultiparmValue )
    {
        // Keys have been removed.
        bIsCurveUploadRequired = true;
        RemoveElements( MultiparmValue - RichCurve.GetNumKeys() );
    }
    else if ( RichCurve.GetNumKeys() > MultiparmValue )
    {
        // Keys have been added.
        bIsCurveUploadRequired = true;
        AddElements( RichCurve.GetNumKeys() - MultiparmValue );
    }
    else
    {
        // We have curve point modification.
        bIsCurveChanged = true;
    }
}

void
UHoudiniAssetParameterRamp::OnCurveColorChanged( UHoudiniAssetParameterRampCurveColor * CurveColor )
{
    if ( !CurveColor )
        return;

    EHoudiniAssetParameterRampCurveColorEvent::Type ColorEvent = CurveColor->GetColorEvent();
    switch( ColorEvent )
    {
        case EHoudiniAssetParameterRampCurveColorEvent::AddStop:
        {
            bIsCurveUploadRequired = true;
            AddElement();
            break;
        }

        case EHoudiniAssetParameterRampCurveColorEvent::RemoveStop:
        {
            bIsCurveUploadRequired = true;
            RemoveElement();
            break;
        }

        case EHoudiniAssetParameterRampCurveColorEvent::ChangeStopTime:
        case EHoudiniAssetParameterRampCurveColorEvent::ChangeStopColor:
        case EHoudiniAssetParameterRampCurveColorEvent::MoveStop:
        {
            // We have curve point modification.
            bIsCurveChanged = true;
            OnCurveEditingFinished();
            break;
        }

        default:
        {
            break;
        }
    }

    CurveColor->ResetColorEvent();
}

void
UHoudiniAssetParameterRamp::OnCurveEditingFinished()
{
    if ( bIsCurveChanged )
    {
        if ( MultiparmValue * 3 != ChildParameters.Num() )
            return;

        bIsCurveChanged = false;

        if ( HoudiniAssetParameterRampCurveFloat )
        {
            FRichCurve & RichCurve = HoudiniAssetParameterRampCurveFloat->FloatCurve;

            MarkPreChanged();

			//JC: get a copy of the keys array so that we can access it by index
			const TArray<FRichCurveKey> RichCurveKeysCopy = RichCurve.GetCopyOfKeys();

            // We need to update ramp key positions.
            for ( int32 KeyIdx = 0, KeyNum = RichCurve.GetNumKeys(); KeyIdx < KeyNum; ++KeyIdx )
            {
                UHoudiniAssetParameterFloat * ChildParamPosition = nullptr;
                UHoudiniAssetParameterFloat * ChildParamValue = nullptr;
                UHoudiniAssetParameterChoice * ChildParamInterpolation = nullptr;

                if ( !GetRampKeysCurveFloat( KeyIdx, ChildParamPosition, ChildParamValue, ChildParamInterpolation ) )
                    continue;

				const FRichCurveKey & RichCurveKey = RichCurveKeysCopy[ KeyIdx ];

                ChildParamPosition->SetValue( RichCurveKey.Time, 0, false, false );
                ChildParamValue->SetValue( RichCurveKey.Value, 0, false, false );

                EHoudiniAssetParameterRampKeyInterpolation::Type RichCurveKeyInterpolation =
                    TranslateUnrealRampKeyInterpolation( RichCurveKey.InterpMode );

                ChildParamInterpolation->SetValueInt( (int32) RichCurveKeyInterpolation, false, false );
            }

            MarkChanged();
        }
        else if ( HoudiniAssetParameterRampCurveColor )
        {
            FRichCurve & RichCurveR = HoudiniAssetParameterRampCurveColor->FloatCurves[ 0 ];
            FRichCurve & RichCurveG = HoudiniAssetParameterRampCurveColor->FloatCurves[ 1 ];
            FRichCurve & RichCurveB = HoudiniAssetParameterRampCurveColor->FloatCurves[ 2 ];
            FRichCurve & RichCurveA = HoudiniAssetParameterRampCurveColor->FloatCurves[ 3 ];

			//JC: get a copy of the keys array so that we can access it by index
			const TArray<FRichCurveKey> RichCurveRKeysCopy = RichCurveR.GetCopyOfKeys();
			const TArray<FRichCurveKey> RichCurveGKeysCopy = RichCurveG.GetCopyOfKeys();
			const TArray<FRichCurveKey> RichCurveBKeysCopy = RichCurveB.GetCopyOfKeys();

            MarkPreChanged();

            // We need to update ramp key positions.
            for ( int32 KeyIdx = 0, KeyNum = RichCurveR.GetNumKeys(); KeyIdx < KeyNum; ++KeyIdx )
            {
                UHoudiniAssetParameterFloat * ChildParamPosition = nullptr;
                UHoudiniAssetParameterColor * ChildParamColor = nullptr;
                UHoudiniAssetParameterChoice * ChildParamInterpolation = nullptr;

                if ( !GetRampKeysCurveColor( KeyIdx, ChildParamPosition, ChildParamColor, ChildParamInterpolation ) )
                    continue;

				const FRichCurveKey & RichCurveKeyR = RichCurveRKeysCopy[ KeyIdx ];
				const FRichCurveKey & RichCurveKeyG = RichCurveGKeysCopy[ KeyIdx ];
				const FRichCurveKey & RichCurveKeyB = RichCurveBKeysCopy[ KeyIdx ];
                //const FRichCurveKey & RichCurveKeyA = RichCurveA.Keys[ KeyIdx ];

                ChildParamPosition->SetValue( RichCurveKeyR.Time, 0, false, false );

                FLinearColor KeyColor( RichCurveKeyR.Value, RichCurveKeyG.Value, RichCurveKeyB.Value, 1.0f );
                ChildParamColor->OnPaintColorChanged( KeyColor, false, false );

                EHoudiniAssetParameterRampKeyInterpolation::Type RichCurveKeyInterpolation =
                    TranslateUnrealRampKeyInterpolation( RichCurveKeyR.InterpMode );

                ChildParamInterpolation->SetValueInt( (int32) RichCurveKeyInterpolation, false, false );
            }

            MarkChanged();
        }
    }
}

void
UHoudiniAssetParameterRamp::AddReferencedObjects( UObject * InThis, FReferenceCollector & Collector )
{
    UHoudiniAssetParameterRamp * HoudiniAssetParameterRamp = Cast< UHoudiniAssetParameterRamp >( InThis );
    if ( HoudiniAssetParameterRamp )
    {
        if ( HoudiniAssetParameterRamp->HoudiniAssetParameterRampCurveFloat )
            Collector.AddReferencedObject( HoudiniAssetParameterRamp->HoudiniAssetParameterRampCurveFloat, InThis );

        if ( HoudiniAssetParameterRamp->HoudiniAssetParameterRampCurveColor )
            Collector.AddReferencedObject( HoudiniAssetParameterRamp->HoudiniAssetParameterRampCurveColor, InThis );
    }

    // Call base implementation.
    Super::AddReferencedObjects( InThis, Collector );
}

void
UHoudiniAssetParameterRamp::Serialize( FArchive & Ar )
{
    // Call base implementation.
    Super::Serialize( Ar );

    Ar.UsingCustomVersion( FHoudiniCustomSerializationVersion::GUID );

    Ar << HoudiniAssetParameterRampCurveFloat;
    Ar << HoudiniAssetParameterRampCurveColor;

    Ar << bIsFloatRamp;

    if ( Ar.IsLoading() )
    {
        bIsCurveChanged = false;
        bIsCurveUploadRequired = false;
    }
}

void
UHoudiniAssetParameterRamp::PostLoad()
{
    Super::PostLoad();

    if ( HoudiniAssetParameterRampCurveFloat )
        HoudiniAssetParameterRampCurveFloat->SetParentRampParameter( this );

    if ( HoudiniAssetParameterRampCurveColor )
        HoudiniAssetParameterRampCurveColor->SetParentRampParameter( this );
}

void
UHoudiniAssetParameterRamp::GenerateCurvePoints()
{
    if ( ChildParameters.Num() % 3 != 0 )
    {
        HOUDINI_LOG_MESSAGE(
            TEXT( "Invalid Ramp parameter [%s] : Number of child parameters is not a tuple of 3." ),
            *ParameterName );

        return;
    }

    if ( HoudiniAssetParameterRampCurveFloat )
    {
        HoudiniAssetParameterRampCurveFloat->ResetCurve();

        for ( int32 ChildIdx = 0, ChildNum = GetRampKeyCount(); ChildIdx < ChildNum; ++ChildIdx )
        {
            UHoudiniAssetParameterFloat * ChildParamPosition = nullptr;
            UHoudiniAssetParameterFloat * ChildParamValue = nullptr;
            UHoudiniAssetParameterChoice * ChildParamInterpolation = nullptr;

            if ( !GetRampKeysCurveFloat(ChildIdx, ChildParamPosition, ChildParamValue, ChildParamInterpolation ) )
            {
                HoudiniAssetParameterRampCurveFloat->ResetCurve();
                return;
            }

            float CurveKeyPosition = ChildParamPosition->GetParameterValue( 0, 0.0f );
            float CurveKeyValue = ChildParamValue->GetParameterValue( 0, 0.0f );
            EHoudiniAssetParameterRampKeyInterpolation::Type RampKeyInterpolation =
                TranslateChoiceKeyInterpolation( ChildParamInterpolation );
            ERichCurveInterpMode RichCurveInterpMode = TranslateHoudiniRampKeyInterpolation( RampKeyInterpolation );

            FRichCurve & RichCurve = HoudiniAssetParameterRampCurveFloat->FloatCurve;

            FKeyHandle const KeyHandle = RichCurve.AddKey( CurveKeyPosition, CurveKeyValue );
            RichCurve.SetKeyInterpMode( KeyHandle, RichCurveInterpMode );
        }
    }
    else if ( HoudiniAssetParameterRampCurveColor )
    {
        HoudiniAssetParameterRampCurveColor->ResetCurve();

        for ( int32 ChildIdx = 0, ChildNum = GetRampKeyCount(); ChildIdx < ChildNum; ++ChildIdx )
        {
            UHoudiniAssetParameterFloat * ChildParamPosition = nullptr;
            UHoudiniAssetParameterColor * ChildParamColor = nullptr;
            UHoudiniAssetParameterChoice * ChildParamInterpolation = nullptr;

            if ( !GetRampKeysCurveColor( ChildIdx, ChildParamPosition, ChildParamColor, ChildParamInterpolation ) )
            {
                HoudiniAssetParameterRampCurveColor->ResetCurve();
                return;
            }

            float CurveKeyPosition = ChildParamPosition->GetParameterValue( 0, 0.0f );
            FLinearColor CurveKeyValue = ChildParamColor->GetColor();
            EHoudiniAssetParameterRampKeyInterpolation::Type RampKeyInterpolation =
                TranslateChoiceKeyInterpolation( ChildParamInterpolation );
            ERichCurveInterpMode RichCurveInterpMode = TranslateHoudiniRampKeyInterpolation( RampKeyInterpolation );

            for ( int CurveIdx = 0; CurveIdx < 4; ++CurveIdx )
            {
                FRichCurve & RichCurve = HoudiniAssetParameterRampCurveColor->FloatCurves[ CurveIdx ];

                FKeyHandle const KeyHandle =
                    RichCurve.AddKey( CurveKeyPosition, CurveKeyValue.Component( CurveIdx ) );
                RichCurve.SetKeyInterpMode( KeyHandle, RichCurveInterpMode );
            }
        }
    }
}

bool
UHoudiniAssetParameterRamp::GetRampKeysCurveFloat(
    int32 Idx, UHoudiniAssetParameterFloat *& Position,
    UHoudiniAssetParameterFloat *& Value,
    UHoudiniAssetParameterChoice *& Interp ) const
{
    Position = nullptr;
    Value = nullptr;
    Interp = nullptr;

    int32 NumChildren = ChildParameters.Num();

    if ( 3 * Idx + 0 < NumChildren )
        Position = Cast< UHoudiniAssetParameterFloat >(ChildParameters[ 3 * Idx + 0 ] );

    if ( 3 * Idx + 1 < NumChildren )
        Value = Cast< UHoudiniAssetParameterFloat >( ChildParameters[ 3 * Idx + 1 ] );

    if ( 3 * Idx + 2 < NumChildren )
        Interp = Cast< UHoudiniAssetParameterChoice >( ChildParameters[ 3 * Idx + 2 ] );

    return Position != nullptr && Value != nullptr && Interp != nullptr;
}

bool
UHoudiniAssetParameterRamp::GetRampKeysCurveColor(
    int32 Idx, UHoudiniAssetParameterFloat *& Position,
    UHoudiniAssetParameterColor *& Value,
    UHoudiniAssetParameterChoice *& Interp ) const
{
    Position = nullptr;
    Value = nullptr;
    Interp = nullptr;

    int32 NumChildren = ChildParameters.Num();

    if ( 3 * Idx + 0 < NumChildren )
        Position = Cast< UHoudiniAssetParameterFloat >( ChildParameters[ 3 * Idx + 0 ] );

    if ( 3 * Idx + 1 < NumChildren )
        Value = Cast< UHoudiniAssetParameterColor >( ChildParameters[ 3 * Idx + 1 ] );

    if ( 3 * Idx + 2 < NumChildren )
        Interp = Cast< UHoudiniAssetParameterChoice >( ChildParameters[ 3 * Idx + 2 ] );

    return Position != nullptr && Value != nullptr && Interp != nullptr;
}

int32
UHoudiniAssetParameterRamp::GetRampKeyCount() const
{
    int32 ChildParamCount = ChildParameters.Num();

    if ( ChildParamCount % 3 != 0 )
    {
        HOUDINI_LOG_MESSAGE(
            TEXT( "Invalid Ramp parameter [%s] : Number of child parameters is not a tuple of 3." ),
            *ParameterName );

        return 0;
    }

    return ChildParamCount / 3;
}

EHoudiniAssetParameterRampKeyInterpolation::Type
UHoudiniAssetParameterRamp::TranslateChoiceKeyInterpolation( UHoudiniAssetParameterChoice * ChoiceParam ) const
{
    EHoudiniAssetParameterRampKeyInterpolation::Type ChoiceInterpolationValue =
        UHoudiniAssetParameterRamp::DefaultUnknownInterpolation;

    if ( ChoiceParam )
    {
        if ( ChoiceParam->IsStringChoiceList() )
        {
            const FString & ChoiceValueString = ChoiceParam->GetParameterValueString();

            if ( ChoiceValueString.Equals( TEXT( HAPI_UNREAL_RAMP_KEY_INTERPOLATION_CONSTANT ) ) )
                ChoiceInterpolationValue = EHoudiniAssetParameterRampKeyInterpolation::Constant;
            else if ( ChoiceValueString.Equals( TEXT( HAPI_UNREAL_RAMP_KEY_INTERPOLATION_LINEAR ) ) )
                ChoiceInterpolationValue = EHoudiniAssetParameterRampKeyInterpolation::Linear;
            else if ( ChoiceValueString.Equals( TEXT( HAPI_UNREAL_RAMP_KEY_INTERPOLATION_CATMULL_ROM ) ) )
                ChoiceInterpolationValue = EHoudiniAssetParameterRampKeyInterpolation::CatmullRom;
            else if ( ChoiceValueString.Equals( TEXT( HAPI_UNREAL_RAMP_KEY_INTERPOLATION_MONOTONE_CUBIC ) ) )
                ChoiceInterpolationValue = EHoudiniAssetParameterRampKeyInterpolation::MonotoneCubic;
            else if ( ChoiceValueString.Equals( TEXT( HAPI_UNREAL_RAMP_KEY_INTERPOLATION_BEZIER ) ) )
                ChoiceInterpolationValue = EHoudiniAssetParameterRampKeyInterpolation::Bezier;
            else if ( ChoiceValueString.Equals( TEXT( HAPI_UNREAL_RAMP_KEY_INTERPOLATION_B_SPLINE ) ) )
                ChoiceInterpolationValue = EHoudiniAssetParameterRampKeyInterpolation::BSpline;
            else if ( ChoiceValueString.Equals( TEXT( HAPI_UNREAL_RAMP_KEY_INTERPOLATION_HERMITE ) ) )
                ChoiceInterpolationValue = EHoudiniAssetParameterRampKeyInterpolation::Hermite;
        }
        else
        {
            int ChoiceValueInt = ChoiceParam->GetParameterValueInt();
            if ( ChoiceValueInt >= 0 || ChoiceValueInt <= 6 )
                ChoiceInterpolationValue = (EHoudiniAssetParameterRampKeyInterpolation::Type) ChoiceValueInt;
        }
    }

    return ChoiceInterpolationValue;
}

ERichCurveInterpMode
UHoudiniAssetParameterRamp::TranslateHoudiniRampKeyInterpolation(
    EHoudiniAssetParameterRampKeyInterpolation::Type KeyInterpolation ) const
{
    switch ( KeyInterpolation )
    {
        case EHoudiniAssetParameterRampKeyInterpolation::Constant:
            return ERichCurveInterpMode::RCIM_Constant;

        case EHoudiniAssetParameterRampKeyInterpolation::Linear:
            return ERichCurveInterpMode::RCIM_Linear;

        default:
            break;
    }

    return ERichCurveInterpMode::RCIM_Cubic;
}

EHoudiniAssetParameterRampKeyInterpolation::Type
UHoudiniAssetParameterRamp::TranslateUnrealRampKeyInterpolation( ERichCurveInterpMode RichCurveInterpMode ) const
{
    switch ( RichCurveInterpMode )
    {
        case ERichCurveInterpMode::RCIM_Constant:
            return EHoudiniAssetParameterRampKeyInterpolation::Constant;

        case ERichCurveInterpMode::RCIM_Linear:
            return EHoudiniAssetParameterRampKeyInterpolation::Linear;

        case ERichCurveInterpMode::RCIM_Cubic:
            return UHoudiniAssetParameterRamp::DefaultSplineInterpolation;

		//case ERichCurveInterpMode::RCIM_None:
        default:
            break;
    }

    return UHoudiniAssetParameterRamp::DefaultUnknownInterpolation;
}
