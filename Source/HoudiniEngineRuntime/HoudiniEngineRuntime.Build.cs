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

    Houdini Version: 16.5.425
    Houdini Engine Version: 3.1.13
    Unreal Version: 4.5.0 (ARK)

*/

using UnrealBuildTool;
using System;
using System.IO;

public class HoudiniEngineRuntime : ModuleRules
{
    public HoudiniEngineRuntime( TargetInfo Target )
    {
        PCHUsage = PCHUsageMode.UseSharedPCHs;
        string HFSPath = "Houdini";
        string HoudiniVersion = "16.5.425";
        PlatformID platformId = Environment.OSVersion.Platform;

        // Check if we are compiling on unsupported platforms.
        if( Target.Platform != UnrealTargetPlatform.Win64 &&
            Target.Platform != UnrealTargetPlatform.Mac &&
            Target.Platform != UnrealTargetPlatform.Linux)
        {
            System.Console.WriteLine( string.Format( "Houdini Engine : Compiling on untested platform.  Please let us know how it goes!" ) );
        }

        string HAPIIncludePath = "";

        if( HFSPath != "" )
        {
            HAPIIncludePath = HFSPath + "/toolkit/include/HAPI";

            if( platformId == PlatformID.Win32NT )
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
                "HoudiniEngineRuntime/Public"
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                "HoudiniEngineRuntime/Private"
            }
        );

        // Add common dependencies.
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
				"CoreUObject",
				"Engine",
				"RenderCore",
				"ShaderCore",
				"InputCore",
				"RHI",
                "EngineSettings",
                "Settings",
                //"UnrealEd",
				//"AssetTools",
				//"Slate",
				//"SlateCore",
				//"Projects",
				//"PropertyEditor",
				//"ContentBrowser",

                /*
				"RawMesh",
                "Settings",
				"TargetPlatform",
				//"LevelEditor",
				"MainFrame",
				//"EditorStyle",
				//"EditorWidgets",
				"AppFramework"
                */
             }
        );

        if (UEBuildConfiguration.bBuildEditor == true)
        {
            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "UnrealEd",
                    "AssetTools",
                }
            );
        }

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Slate",
                "SlateCore",
                "Projects",
            }
        );

        if (UEBuildConfiguration.bBuildEditor == true)
        {
            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    //"UnrealEd",
				    //"AssetTools",
				    //"Slate",
				    //"SlateCore",
				    
				    "PropertyEditor",
				    "ContentBrowser",
				    "LevelEditor",
				    "EditorStyle",
				    "EditorWidgets",
                    "MainFrame",
                }
            );
        }

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
				"RawMesh",
				"TargetPlatform",
				//"LevelEditor",
				//"EditorStyle",
				//"EditorWidgets",
				"AppFramework"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                // ... add private dependencies that you statically link with here ...
            }
        );

        //if (Target.bBuildEditor == true)
        //{
        PrivateDependencyModuleNames.AddRange(
        new string[]
        {

        }
        );
        //}

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
        );
    }
}
