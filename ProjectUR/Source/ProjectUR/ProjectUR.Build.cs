// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectUR : ModuleRules
{
	public ProjectUR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", "CoreUObject", "Engine", "InputCore", 
			"EnhancedInput", "UMG", "Niagara", "Slate", "SlateCore", 
			"GameplayAbilities", "GameplayTags", "GameplayTasks" ,
            "AIModule"

        });
		PrivateDependencyModuleNames.AddRange(new string[] { "CableComponent" });
    }
}
