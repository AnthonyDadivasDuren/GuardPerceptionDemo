// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GuardPerceptionDemo : ModuleRules
{
	public GuardPerceptionDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GuardPerceptionDemo",
			"GuardPerceptionDemo/Variant_Horror",
			"GuardPerceptionDemo/Variant_Horror/UI",
			"GuardPerceptionDemo/Variant_Shooter",
			"GuardPerceptionDemo/Variant_Shooter/AI",
			"GuardPerceptionDemo/Variant_Shooter/UI",
			"GuardPerceptionDemo/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
