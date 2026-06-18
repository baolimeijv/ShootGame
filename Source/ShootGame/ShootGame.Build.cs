// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootGame : ModuleRules
{
	public ShootGame(ReadOnlyTargetRules Target) : base(Target)
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
			"ShootGame",
			"ShootGame/Variant_Platforming",
			"ShootGame/Variant_Platforming/Animation",
			"ShootGame/Variant_Combat",
			"ShootGame/Variant_Combat/AI",
			"ShootGame/Variant_Combat/Animation",
			"ShootGame/Variant_Combat/Gameplay",
			"ShootGame/Variant_Combat/Interfaces",
			"ShootGame/Variant_Combat/UI",
			"ShootGame/Variant_SideScrolling",
			"ShootGame/Variant_SideScrolling/AI",
			"ShootGame/Variant_SideScrolling/Gameplay",
			"ShootGame/Variant_SideScrolling/Interfaces",
			"ShootGame/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
