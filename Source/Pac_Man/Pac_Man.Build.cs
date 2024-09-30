// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Pac_Man : ModuleRules
{
	public Pac_Man(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","AIModule","NavigationSystem" });
	}
}
