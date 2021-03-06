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

#pragma once

#include "HoudiniAssetParameter.h"
#include "Core.h"
#include "HoudiniAssetParameterColor.generated.h"


UCLASS()
class HOUDINIENGINERUNTIME_API UHoudiniAssetParameterColor : public UHoudiniAssetParameter
{
    GENERATED_UCLASS_BODY()

    friend struct FHoudiniParameterDetails;

    public:

        /** Create instance of this class. **/
        static UHoudiniAssetParameterColor* Create(
            UObject * InPrimaryObject,
            UHoudiniAssetParameter * InParentParameter,
            HAPI_NodeId InNodeId,
            const HAPI_ParmInfo & ParmInfo );

    public:

        /** Create this parameter from HAPI information. **/
        virtual bool CreateParameter(
            UObject * InPrimaryObject,
            UHoudiniAssetParameter * InParentParameter,
            HAPI_NodeId InNodeId,
            const HAPI_ParmInfo & ParmInfo ) override;

        /** Upload parameter value to HAPI. **/
        virtual bool UploadParameterValue() override;

        /** Set parameter value. **/
        virtual bool SetParameterVariantValue(
            const FVariant & Variant, int32 Idx = 0, bool bTriggerModify = true,
            bool bRecordUndo = true ) override;

    /** UObject methods. **/
    public:

        virtual void Serialize( FArchive & Ar ) override;

    public:

        /** Return color for this color parameter. **/
        FLinearColor GetColor() const;

#if WITH_EDITOR

        /** Handle mouse click on color box. **/
        FReply OnColorBlockMouseButtonDown( const FGeometry & MyGeometry, const FPointerEvent & MouseEvent );

#endif

        /** Called when new color is selected. **/
        void OnPaintColorChanged( FLinearColor InNewColor, bool bTriggerModify = true, bool bRecordUndo = true );

    protected:

        /** Color for this property. **/
        FLinearColor Color;
};
