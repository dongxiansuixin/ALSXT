// MIT

#include "AlsxtCharacterMovementComponent.h"
#include "Utility/AlsxtGameplayTags.h"
#include "Interfaces/AlsxtCharacterInterface.h"

void UAlsxtCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

FVector UAlsxtCharacterMovementComponent::ConsumeInputVector()
{
	// return Super::ConsumeInputVector();

	if (IAlsxtCharacterInterface::Execute_GetCharacterStatus(GetOwner()) == ALSXTStatusTags::Normal)
	{
		return Super::ConsumeInputVector();
	}
	else
	{
		return FVector::ZeroVector;
	}
}

float UAlsxtCharacterMovementComponent::GetMaxSpeed() const
{
	return Super::GetMaxSpeed() * MovementSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetStandingWalkSpeedMultiplier() const
{
	return StandingWalkSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetStandingAimingSpeedMultiplier() const
{
	return StandingAimingSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetStandingCombatSpeedMultiplier() const
{
	return StandingCombatSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetStandingRunSpeedMultiplier() const
{
	return StandingRunSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetStandingSprintSpeedMultiplier() const
{
	return StandingSprintSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetCrouchedWalkSpeedMultiplier() const
{
	return CrouchedWalkSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetCrouchedAimingSpeedMultiplier() const
{
	return CrouchedAimingSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetCrouchedCombatSpeedMultiplier() const
{
	return CrouchedCombatSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetCrouchedRunSpeedMultiplier() const
{
	return CrouchedRunSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetCrouchedSprintSpeedMultiplier() const
{
	return CrouchedSprintSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetProneWalkSpeedMultiplier() const
{
	return ProneWalkSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetProneAimingSpeedMultiplier() const
{
	return ProneAimingSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetProneCombatSpeedMultiplier() const
{
	return ProneCombatSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetProneRunSpeedMultiplier() const
{
	return ProneRunSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetProneSprintSpeedMultiplier() const
{
	return ProneSprintSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetClimbingWalkSpeedMultiplier() const
{
	return ClimbingWalkSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetClimbingAimingSpeedMultiplier() const
{
	return ClimbingAimingSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetClimbingCombatSpeedMultiplier() const
{
	return ClimbingCombatSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetClimbingRunSpeedMultiplier() const
{
	return ClimbingRunSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetClimbingSprintSpeedMultiplier() const
{
	return ClimbingSprintSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetSwimmingWalkSpeedMultiplier() const
{
	return SwimmingWalkSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetSwimmingAimingSpeedMultiplier() const
{
	return SwimmingAimingSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetSwimmingCombatSpeedMultiplier() const
{
	return SwimmingCombatSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetSwimmingRunSpeedMultiplier() const
{
	return SwimmingRunSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetSwimmingSprintSpeedMultiplier() const
{
	return SwimmingSprintSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxStandingWalkSpeed() const
{
	return Super::GetMaxSpeed() * StandingWalkSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxStandingAimingSpeed() const
{
	return Super::GetMaxSpeed() * StandingAimingSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxStandingCombatSpeed() const
{
	return Super::GetMaxSpeed() * StandingCombatSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxStandingRunSpeed() const
{
	return Super::GetMaxSpeed() * StandingRunSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxStandingSprintSpeed() const
{
	return Super::GetMaxSpeed() * StandingSprintSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxCrouchedWalkSpeed() const
{
	return Super::GetMaxSpeed() * CrouchedWalkSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxCrouchedAimingSpeed() const
{
	return Super::GetMaxSpeed() * CrouchedAimingSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxCrouchedCombatSpeed() const
{
	return Super::GetMaxSpeed() * CrouchedCombatSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxCrouchedRunSpeed() const
{
	return Super::GetMaxSpeed() * CrouchedRunSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxCrouchedSprintSpeed() const
{
	return Super::GetMaxSpeed() * CrouchedSprintSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxProneWalkSpeed() const
{
	return Super::GetMaxSpeed() * ProneWalkSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxProneAimingSpeed() const
{
	return Super::GetMaxSpeed() * ProneAimingSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxProneCombatSpeed() const
{
	return Super::GetMaxSpeed() * ProneCombatSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxProneRunSpeed() const
{
	return Super::GetMaxSpeed() * ProneRunSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxProneSprintSpeed() const
{
	return Super::GetMaxSpeed() * ProneSprintSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxClimbingWalkSpeed() const
{
	return Super::GetMaxSpeed() * ClimbingWalkSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxClimbingAimingSpeed() const
{
	return Super::GetMaxSpeed() * ClimbingAimingSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxClimbingCombatSpeed() const
{
	return Super::GetMaxSpeed() * ClimbingCombatSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxClimbingRunSpeed() const
{
	return Super::GetMaxSpeed() * ClimbingRunSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxClimbingSprintSpeed() const
{
	return Super::GetMaxSpeed() * ClimbingSprintSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxSwimmingWalkSpeed() const
{
	return Super::GetMaxSpeed() * SwimmingWalkSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxSwimmingAimingSpeed() const
{
	return Super::GetMaxSpeed() * SwimmingAimingSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxSwimmingCombatSpeed() const
{
	return Super::GetMaxSpeed() * SwimmingCombatSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxSwimmingRunSpeed() const
{
	return Super::GetMaxSpeed() * SwimmingRunSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxSwimmingSprintSpeed() const
{
	return Super::GetMaxSpeed() * SwimmingSprintSpeedMultiplier;
}

float UAlsxtCharacterMovementComponent::GetMaxAcceleration() const
{
	return Super::GetMaxAcceleration();
}

void UAlsxtCharacterMovementComponent::SetMovementSpeedMultiplier(float Multiplier)
{
	MovementSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetStandingWalkSpeedMultiplier(float Multiplier)
{
	StandingWalkSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetStandingAimingSpeedMultiplier(float Multiplier)
{
	StandingAimingSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetStandingCombatSpeedMultiplier(float Multiplier)
{
	StandingCombatSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetStandingRunSpeedMultiplier(float Multiplier)
{
	StandingRunSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetStandingSprintSpeedMultiplier(float Multiplier)
{
	StandingSprintSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetCrouchedWalkSpeedMultiplier(float Multiplier)
{
	CrouchedWalkSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetCrouchedAimingSpeedMultiplier(float Multiplier)
{
	CrouchedAimingSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetCrouchedCombatSpeedMultiplier(float Multiplier)
{
	CrouchedCombatSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetCrouchedRunSpeedMultiplier(float Multiplier)
{
	CrouchedRunSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetCrouchedSprintSpeedMultiplier(float Multiplier)
{
	CrouchedSprintSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetProneWalkSpeedMultiplier(float Multiplier)
{
	ProneWalkSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetProneAimingSpeedMultiplier(float Multiplier)
{
	ProneAimingSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetProneCombatSpeedMultiplier(float Multiplier)
{
	ProneCombatSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetProneRunSpeedMultiplier(float Multiplier)
{
	ProneRunSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetProneSprintSpeedMultiplier(float Multiplier)
{
	ProneSprintSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetClimbingWalkSpeedMultiplier(float Multiplier)
{
	ClimbingWalkSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetClimbingAimingSpeedMultiplier(float Multiplier)
{
	ClimbingAimingSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetClimbingCombatSpeedMultiplier(float Multiplier)
{
	ClimbingCombatSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetClimbingRunSpeedMultiplier(float Multiplier)
{
	ClimbingRunSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetClimbingSprintSpeedMultiplier(float Multiplier)
{
	ClimbingSprintSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetSwimmingWalkSpeedMultiplier(float Multiplier)
{
	SwimmingWalkSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetSwimmingAimingSpeedMultiplier(float Multiplier)
{
	SwimmingAimingSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetSwimmingCombatSpeedMultiplier(float Multiplier)
{
	SwimmingCombatSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetSwimmingRunSpeedMultiplier(float Multiplier)
{
	SwimmingRunSpeedMultiplier = Multiplier;
}

void UAlsxtCharacterMovementComponent::SetSwimmingSprintSpeedMultiplier(float Multiplier)
{
	SwimmingSprintSpeedMultiplier = Multiplier;
}