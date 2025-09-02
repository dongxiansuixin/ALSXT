using UnrealBuildTool;

public class ALSXT : ModuleRules
{
	public ALSXT(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		// CppCompileWarningSettings.UnsafeTypeCastWarningLevel = WarningLevel.Warning;
		CppCompileWarningSettings.NonInlinedGenCppWarningLevel = WarningLevel.Warning;

		PublicDependencyModuleNames.AddRange([
			"Core",
			"Landscape",
			"CoreUObject",
			"Engine",
			"AudioExtensions",
			"UMG",
			"GameplayTags",
			"GameplayCameras",
			"CinematicCamera",
			"AIModule",
			"AnimGraphRuntime",
			"RigVM",
			"ControlRig",
			"EnhancedInput",
			"ALS",
			"ALSCamera",
			"Niagara",
			"NetCore",
			"NetCommon",
			"Networking",
			"GameFeatures",
			"ModularGameplay",
			"ModularGameplayActors",
			"AbilitySystemGameFeatureActions",
			"GameplayTasks",
			"Chooser",
			"ContextualAnimation",
			"DataRegistry",
#if UE_5_5_OR_LATER
			// pass
#else
			"StructUtils",
#endif // UE_5_5_OR_LATER
		]);			
		
		PrivateDependencyModuleNames.AddRange([
			"EngineSettings",
			"PhysicsCore",
			"Slate",
			"SlateCore",
			"GameplayAbilities",
			"TargetingSystem"
		]);

		if (Target.Type == TargetRules.TargetType.Editor)
		{
			PrivateDependencyModuleNames.AddRange([
				"MessageLog"
			]);
		}

		SetupIrisSupport(Target);
	}
}
