// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Spirit : ModuleRules
{
	public Spirit(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


		PublicDependencyModuleNames.AddRange(new string[] {
            "Json",
			"JsonUtilities",
            "Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"UMG",
            "CommonUI",
            "EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"Niagara",
			"MotionTrajectory"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
				"NakamaUnreal",
				"NakamaCore",
				"GameplayAbilities",
				"GameplayTags",
				"GameplayTasks"
		});
    }
}
