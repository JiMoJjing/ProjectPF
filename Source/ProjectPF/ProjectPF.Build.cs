// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectPF : ModuleRules
{
	public ProjectPF(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });

        PublicIncludePaths.Add(ModuleDirectory);
		//PublicIncludePaths.AddRange(new string[] {"Source/Character"});
    }
}
