#pragma once

#include "Engine/DataAsset.h"
#include "Utility/AlsGameplayTags.h"
#include "Utility/AlsxtGameplayTags.h"
#include "AlsxtMovementSettings.generated.h"

struct FAlsMovementStanceSettings;
class UCurveFloat;
class UCurveVector;

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtMovementGaitSettings
{
	GENERATED_BODY()

public:
	// Currently, the direction-dependent movement speed can cause some jitter in multiplayer, so enable it at your own risk.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS")
	uint8 bAllowDirectionDependentMovementSpeed : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float StandingWalkForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float StandingWalkBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float StandingAimingForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float StandingAimingBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float StandingCombatForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float StandingCombatBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float StandingRunForwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float StandingRunBackwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float StandingSprintSpeed{650.0f};

	//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float CrouchedWalkForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float CrouchedWalkBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float CrouchedAimingForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float CrouchedAimingBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float CrouchedCombatForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float CrouchedCombatBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float CrouchedRunForwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float CrouchedRunBackwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float CrouchedSprintSpeed{650.0f};

	//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float ProneWalkForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float ProneWalkBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float ProneAimingForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float ProneAimingBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float ProneCombatForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float ProneCombatBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float ProneRunForwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float ProneRunBackwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float ProneSprintSpeed{650.0f};

	//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float ClimbingWalkForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float ClimbingWalkBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float ClimbingAimingForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float ClimbingAimingBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float ClimbingCombatForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float ClimbingCombatBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float ClimbingRunForwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float ClimbingRunBackwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float ClimbingSprintSpeed{650.0f};

	//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float SwimmingWalkForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float SwimmingWalkBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float SwimmingAimingForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float SwimmingAimingBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float SwimmingCombatForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float SwimmingCombatBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float SwimmingRunForwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float SwimmingRunBackwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float SwimmingSprintSpeed{650.0f};

	// Gait amount to acceleration, deceleration, and ground friction curve.
	// Gait amount ranges from 0 to 3, where 0 is stopped, 1 is walking, 2 is running, and 3 is sprinting.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	TObjectPtr<UCurveVector> AccelerationAndDecelerationAndGroundFrictionCurve;

	// Gait amount to rotation interpolation speed curve.
	// Gait amount ranges from 0 to 3, where 0 is stopped, 1 is walking, 2 is running, and 3 is sprinting.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	TObjectPtr<UCurveFloat> RotationInterpolationSpeedCurve;

public:
	float GetMaxStandingWalkSpeed() const;
	float GetMaxStandingAimingSpeed() const;
	float GetMaxStandingCombatSpeed() const;
	float GetMaxStandingRunSpeed() const;
	float GetMaxStandingSprintSpeed() const;

	float GetMaxCrouchedWalkSpeed() const;
	float GetMaxCrouchedAimingSpeed() const;
	float GetMaxCrouchedCombatSpeed() const;
	float GetMaxCrouchedRunSpeed() const;
	float GetMaxCrouchedSprintSpeed() const;

	float GetMaxProneWalkSpeed() const;
	float GetMaxProneAimingSpeed() const;
	float GetMaxProneCombatSpeed() const;
	float GetMaxProneRunSpeed() const;
	float GetMaxProneSprintSpeed() const;

	float GetMaxClimbingWalkSpeed() const;
	float GetMaxClimbingAimingSpeed() const;
	float GetMaxClimbingCombatSpeed() const;
	float GetMaxClimbingRunSpeed() const;
	float GetMaxClimbingSprintSpeed() const;

	float GetMaxSwimmingWalkSpeed() const;
	float GetMaxSwimmingAimingSpeed() const;
	float GetMaxSwimmingCombatSpeed() const;
	float GetMaxSwimmingRunSpeed() const;
	float GetMaxSwimmingSprintSpeed() const;
};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtMovementStanceSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceInlineRow))
	TMap<FGameplayTag, FAlsxtMovementGaitSettings> Stances
	{
		{AlsStanceTags::Standing, {}},
		{AlsStanceTags::Crouching, {}},
		{AlsStanceTags::Prone, {}}
		
	};
};

UCLASS(Blueprintable, BlueprintType)
class ALSXT_API UAlsxtMovementSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	// Range of velocity angle relative to the view direction at which
	// interpolation from forward speed to backward speed will take place.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"))
	FVector2f VelocityAngleToSpeedInterpolationRange{100.0f, 125.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ForceInlineRow))
	TMap<FGameplayTag, FAlsxtMovementStanceSettings> RotationModes
	{
		{AlsRotationModeTags::VelocityDirection, {}},
		{AlsRotationModeTags::ViewDirection, {}},
		{AlsRotationModeTags::Aiming, {}}
	};

public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& ChangedEvent) override;
#endif
};

inline float FAlsxtMovementGaitSettings::GetMaxStandingWalkSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(StandingWalkForwardSpeed, StandingWalkBackwardSpeed)
			   : StandingWalkForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxStandingAimingSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(StandingAimingForwardSpeed, StandingAimingBackwardSpeed)
			   : StandingAimingForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxStandingCombatSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(StandingCombatForwardSpeed, StandingCombatBackwardSpeed)
			   : StandingCombatForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxStandingRunSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(StandingWalkForwardSpeed, StandingWalkBackwardSpeed)
			   : StandingWalkForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxStandingSprintSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(StandingWalkForwardSpeed, StandingWalkBackwardSpeed)
			   : StandingWalkForwardSpeed;
}

//

inline float FAlsxtMovementGaitSettings::GetMaxCrouchedWalkSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(CrouchedWalkForwardSpeed, CrouchedWalkBackwardSpeed)
			   : CrouchedWalkForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxCrouchedAimingSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(CrouchedAimingForwardSpeed, CrouchedAimingBackwardSpeed)
			   : CrouchedAimingForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxCrouchedCombatSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(CrouchedCombatForwardSpeed, CrouchedCombatBackwardSpeed)
			   : CrouchedCombatForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxCrouchedRunSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(CrouchedWalkForwardSpeed, CrouchedWalkBackwardSpeed)
			   : CrouchedWalkForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxCrouchedSprintSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(CrouchedWalkForwardSpeed, CrouchedWalkBackwardSpeed)
			   : CrouchedWalkForwardSpeed;
}

//

inline float FAlsxtMovementGaitSettings::GetMaxProneWalkSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(ProneWalkForwardSpeed, ProneWalkBackwardSpeed)
			   : ProneWalkForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxProneAimingSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(ProneAimingForwardSpeed, ProneAimingBackwardSpeed)
			   : ProneAimingForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxProneCombatSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(ProneCombatForwardSpeed, ProneCombatBackwardSpeed)
			   : ProneCombatForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxProneRunSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(ProneWalkForwardSpeed, ProneWalkBackwardSpeed)
			   : ProneWalkForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxProneSprintSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(ProneWalkForwardSpeed, ProneWalkBackwardSpeed)
			   : ProneWalkForwardSpeed;
}

//

inline float FAlsxtMovementGaitSettings::GetMaxClimbingWalkSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(ClimbingWalkForwardSpeed, ClimbingWalkBackwardSpeed)
			   : ClimbingWalkForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxClimbingAimingSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(ClimbingAimingForwardSpeed, ClimbingAimingBackwardSpeed)
			   : ClimbingAimingForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxClimbingCombatSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(ClimbingCombatForwardSpeed, ClimbingCombatBackwardSpeed)
			   : ClimbingCombatForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxClimbingRunSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(ClimbingWalkForwardSpeed, ClimbingWalkBackwardSpeed)
			   : ClimbingWalkForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxClimbingSprintSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(ClimbingWalkForwardSpeed, ClimbingWalkBackwardSpeed)
			   : ClimbingWalkForwardSpeed;
}

//

inline float FAlsxtMovementGaitSettings::GetMaxSwimmingWalkSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(SwimmingWalkForwardSpeed, SwimmingWalkBackwardSpeed)
			   : SwimmingWalkForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxSwimmingAimingSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(SwimmingAimingForwardSpeed, SwimmingAimingBackwardSpeed)
			   : SwimmingAimingForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxSwimmingCombatSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(SwimmingCombatForwardSpeed, SwimmingCombatBackwardSpeed)
			   : SwimmingCombatForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxSwimmingRunSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(SwimmingWalkForwardSpeed, SwimmingWalkBackwardSpeed)
			   : SwimmingWalkForwardSpeed;
}

inline float FAlsxtMovementGaitSettings::GetMaxSwimmingSprintSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
			   ? FMath::Max(SwimmingWalkForwardSpeed, SwimmingWalkBackwardSpeed)
			   : SwimmingWalkForwardSpeed;
}