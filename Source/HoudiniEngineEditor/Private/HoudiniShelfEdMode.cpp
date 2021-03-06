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
#include "HoudiniShelfEdMode.h"
#include "HoudiniEngineEditorPrivatePCH.h"
#include "HoudiniShelfEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "Editor/UnrealEd/Public/EditorModes.h"
#include "Editor/UnrealEd/Public/EditorModeTools.h"
#include "Editor/UnrealEd/Public/EditorModeRegistry.h"
//#include "EditorModeManager.h"

const FEditorModeID FHoudiniShelfEdMode::EM_HoudiniShelfEdModeId = TEXT( "EM_HoudiniShelfEdMode" );

FHoudiniShelfEdMode::FHoudiniShelfEdMode()
{

}

void
FHoudiniShelfEdMode::Enter()
{
    FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		auto ToolkitHost = FModuleManager::LoadModuleChecked< FLevelEditorModule >("LevelEditor").GetFirstLevelEditor();
		Toolkit = MakeShareable(new FHoudiniShelfEdModeToolkit);
		Toolkit->Init(ToolkitHost);
	}
}

void
FHoudiniShelfEdMode::Exit()
{
    if ( Toolkit.IsValid() )
    {
        FToolkitManager::Get().CloseToolkit( Toolkit.ToSharedRef() );
        Toolkit.Reset();
    }

    // Call base Exit method to ensure proper cleanup
    FEdMode::Exit();
}

bool
FHoudiniShelfEdMode::UsesToolkits() const
{
    return true;
}
