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

#include "Core.h"
#include "HoudiniEngineEditor.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/Reply.h"
#include "Widgets/SCompoundWidget.h"
#include "Misc/NotifyHook.h"
#include "Widgets/Input/SCheckBox.h"
#include "HoudiniToolProperties.generated.h"

class IDetailsView;
class ITableRow;
class STableViewBase;
struct FSlateBrush;


// Class describing the various properties for a Houdini Tool
// adding a UClass was necessary to use the PropertyEditor window
UCLASS( EditInlineNew )
class UHoudiniToolProperties : public UObject
{
    GENERATED_UCLASS_BODY()

    public:

        /** Name of the tool */
        UPROPERTY( Category = Tool, EditAnywhere )
        FString Name;

        /** Type of the tool */
        UPROPERTY( Category = Tool, EditAnywhere )
		TEnumAsByte<EHoudiniToolType> Type;

		/** Selection Type of the tool */
		UPROPERTY(Category = Tool, EditAnywhere)
		TEnumAsByte<EHoudiniToolSelectionType> SelectionType;

        /** Tooltip shown on mouse hover */
        UPROPERTY( Category = Tool, EditAnywhere )
        FString ToolTip;

        /** Path to a custom icon */
        UPROPERTY( Category = Tool, EditAnywhere, meta = (FilePathFilter = "png") )
        FFilePath IconPath;

        /** Houdini uasset */
        UPROPERTY( Category = Tool, EditAnywhere )
		TAssetPtr < class UHoudiniAsset > HoudiniAsset;

        /** Clicking on help icon will bring up this URL */
        UPROPERTY( Category = Tool, EditAnywhere )
        FString HelpURL;
};
