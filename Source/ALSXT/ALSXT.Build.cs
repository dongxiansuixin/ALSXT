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
			"Core",	"Landscape", "CoreUObject", "Engine", "AudioExtensions", "UMG", "GameplayTags", "GameplayCameras", "CinematicCamera", "AIModule", "AnimGraphRuntime", "RigVM", "ControlRig", "EnhancedInput", "ALS", "ALSCamera", "Niagara", "NetCore", "StructUtils", "NetCommon", "Networking", "GameFeatures", "ModularGameplay", "ModularGameplayActors", "AbilitySystemGameFeatureActions", "GameplayTasks", "GameplayAbilities"
		]);			
		
		PrivateDependencyModuleNames.AddRange([
			"EngineSettings", "PhysicsCore", "Slate", "SlateCore", "TargetingSystem"
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
