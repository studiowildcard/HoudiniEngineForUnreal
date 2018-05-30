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
 * Produced by:
 *      Side Effects Software Inc
 *      123 Front Street West, Suite 1401
 *      Toronto, Ontario
 *      Canada   M5J 2M2
 *      416-504-9876
 */

/*

    Houdini Version: 16.5.460
    Houdini Engine Version: 3.1.13
    Unreal Version: 4.5.0 (ARK)

*/

using UnrealBuildTool;
using System.IO;

public class HoudiniEngineEditor : ModuleRules
{
    public HoudiniEngineEditor( TargetInfo Target )
    {
        PCHUsage = PCHUsageMode.UseSharedPCHs;
        string HFSPath = "Houdini";
        string HoudiniVersion = "16.5.460";

        // Check if we are compiling on unsupported platforms.
        if( Target.Platform != UnrealTargetPlatform.Win64 &&
            Target.Platform != UnrealTargetPlatform.Mac &&
            Target.Platform != UnrealTargetPlatform.Linux )
        {
            string Err = string.Format( "Houdini Engine Runtime: Compiling on unsupported platform." );
            System.Console.WriteLine( Err );
            throw new BuildException( Err );
        }

        string HAPIIncludePath = "";

        if( HFSPath != "" )
        {
            HAPIIncludePath = HFSPath + "/toolkit/include/HAPI";

            if( Target.Platform == UnrealTargetPlatform.Win64 )
            {
                Definitions.Add( "HOUDINI_ENGINE_HFS_PATH_DEFINE=" + HFSPath );
            }
        }

        if( HAPIIncludePath != "" )
        {
            PublicIncludePaths.Add( HAPIIncludePath );

            // Add the custom include path as well in case the toolkit path doesn't exist yet.
            PublicIncludePaths.Add( HFSPath + "/custom/houdini/include/HAPI" );
        }

        PublicIncludePaths.AddRange(
            new string[] {
                "HoudiniEngineRuntime/Public/HAPI",
                "HoudiniEngineRuntime/Public",
                "HoudiniEngineEditor/Public"
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                "HoudiniEngineEditor/Private",
                "HoudiniEngineRuntime/Private",
            }
        );

        // Add common dependencies.
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "HoudiniEngineRuntime",
                "Slate",
                "SlateCore",
                //"Landscape"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UnrealEd",
                "AppFramework",
                "AssetTools",
                "ContentBrowser",
                "DesktopWidgets",
                "EditorStyle",
                "EditorWidgets",
                "Engine",
                "InputCore",
                "LevelEditor",
                "MainFrame",
                "PlacementMode",
                "Projects",
                "PropertyEditor",
                "RHI",
                "RawMesh",
                "RenderCore",
                "ShaderCore",
                "TargetPlatform",
                //"ApplicationCore",
            }
        );

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
        );
    }
}
