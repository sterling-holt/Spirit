// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Storyteller : ModuleRules
{
	public Storyteller(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
                "Engine",
                "UnrealEd",  // For editor functionality
                "Slate",
                "SlateCore",
                "EditorStyle",
                "Projects",
                "InputCore",
				"AssetTools",
				"AssetRegistry",
				"PropertyEditor",
                "Sequencer",  // For sequencer functionality
                "MovieScene",
                "LevelEditor"
				// ... add other public dependencies that you statically link with here ...
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "AppFramework",
				"WorkspaceMenuStructure"
				// ... add private dependencies that you statically link with here ...	
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
