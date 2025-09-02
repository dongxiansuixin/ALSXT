// MIT

#include "ALSXTCharacterMovementComponent.h"
#include "Utility/ALSXTGameplayTags.h"
#include "Interfaces/AlsxtCharacterInterface.h"

void UALSXTCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

FVector UALSXTCharacterMovementComponent::ConsumeInputVector()
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

float UALSXTCharacterMovementComponent::GetMaxSpeed() const
{
	return Super::GetMaxSpeed() * MovementSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetStandingWalkSpeedMultiplier() const
{
	return StandingWalkSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetStandingAimingSpeedMultiplier() const
{
	return StandingAimingSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetStandingCombatSpeedMultiplier() const
{
	return StandingCombatSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetStandingRunSpeedMultiplier() const
{
	return StandingRunSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetStandingSprintSpeedMultiplier() const
{
	return StandingSprintSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetCrouchedWalkSpeedMultiplier() const
{
	return CrouchedWalkSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetCrouchedAimingSpeedMultiplier() const
{
	return CrouchedAimingSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetCrouchedCombatSpeedMultiplier() const
{
	return CrouchedCombatSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetCrouchedRunSpeedMultiplier() const
{
	return CrouchedRunSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetCrouchedSprintSpeedMultiplier() const
{
	return CrouchedSprintSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetProneWalkSpeedMultiplier() const
{
	return ProneWalkSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetProneAimingSpeedMultiplier() const
{
	return ProneAimingSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetProneCombatSpeedMultiplier() const
{
	return ProneCombatSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetProneRunSpeedMultiplier() const
{
	return ProneRunSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetProneSprintSpeedMultiplier() const
{
	return ProneSprintSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetClimbingWalkSpeedMultiplier() const
{
	return ClimbingWalkSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetClimbingAimingSpeedMultiplier() const
{
	return ClimbingAimingSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetClimbingCombatSpeedMultiplier() const
{
	return ClimbingCombatSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetClimbingRunSpeedMultiplier() const
{
	return ClimbingRunSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetClimbingSprintSpeedMultiplier() const
{
	return ClimbingSprintSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetSwimmingWalkSpeedMultiplier() const
{
	return SwimmingWalkSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetSwimmingAimingSpeedMultiplier() const
{
	return SwimmingAimingSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetSwimmingCombatSpeedMultiplier() const
{
	return SwimmingCombatSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetSwimmingRunSpeedMultiplier() const
{
	return SwimmingRunSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetSwimmingSprintSpeedMultiplier() const
{
	return SwimmingSprintSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxStandingWalkSpeed() const
{
	return Super::GetMaxSpeed() * StandingWalkSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxStandingAimingSpeed() const
{
	return Super::GetMaxSpeed() * StandingAimingSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxStandingCombatSpeed() const
{
	return Super::GetMaxSpeed() * StandingCombatSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxStandingRunSpeed() const
{
	return Super::GetMaxSpeed() * StandingRunSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxStandingSprintSpeed() const
{
	return Super::GetMaxSpeed() * StandingSprintSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxCrouchedWalkSpeed() const
{
	return Super::GetMaxSpeed() * CrouchedWalkSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxCrouchedAimingSpeed() const
{
	return Super::GetMaxSpeed() * CrouchedAimingSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxCrouchedCombatSpeed() const
{
	return Super::GetMaxSpeed() * CrouchedCombatSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxCrouchedRunSpeed() const
{
	return Super::GetMaxSpeed() * CrouchedRunSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxCrouchedSprintSpeed() const
{
	return Super::GetMaxSpeed() * CrouchedSprintSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxProneWalkSpeed() const
{
	return Super::GetMaxSpeed() * ProneWalkSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxProneAimingSpeed() const
{
	return Super::GetMaxSpeed() * ProneAimingSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxProneCombatSpeed() const
{
	return Super::GetMaxSpeed() * ProneCombatSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxProneRunSpeed() const
{
	return Super::GetMaxSpeed() * ProneRunSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxProneSprintSpeed() const
{
	return Super::GetMaxSpeed() * ProneSprintSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxClimbingWalkSpeed() const
{
	return Super::GetMaxSpeed() * ClimbingWalkSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxClimbingAimingSpeed() const
{
	return Super::GetMaxSpeed() * ClimbingAimingSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxClimbingCombatSpeed() const
{
	return Super::GetMaxSpeed() * ClimbingCombatSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxClimbingRunSpeed() const
{
	return Super::GetMaxSpeed() * ClimbingRunSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxClimbingSprintSpeed() const
{
	return Super::GetMaxSpeed() * ClimbingSprintSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxSwimmingWalkSpeed() const
{
	return Super::GetMaxSpeed() * SwimmingWalkSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxSwimmingAimingSpeed() const
{
	return Super::GetMaxSpeed() * SwimmingAimingSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxSwimmingCombatSpeed() const
{
	return Super::GetMaxSpeed() * SwimmingCombatSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxSwimmingRunSpeed() const
{
	return Super::GetMaxSpeed() * SwimmingRunSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxSwimmingSprintSpeed() const
{
	return Super::GetMaxSpeed() * SwimmingSprintSpeedMultiplier;
}

float UALSXTCharacterMovementComponent::GetMaxAcceleration() const
{
	return Super::GetMaxAcceleration();
}

void UALSXTCharacterMovementComponent::SetMovementSpeedMultiplier(float Multiplier)
{
	MovementSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetStandingWalkSpeedMultiplier(float Multiplier)
{
	StandingWalkSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetStandingAimingSpeedMultiplier(float Multiplier)
{
	StandingAimingSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetStandingCombatSpeedMultiplier(float Multiplier)
{
	StandingCombatSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetStandingRunSpeedMultiplier(float Multiplier)
{
	StandingRunSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetStandingSprintSpeedMultiplier(float Multiplier)
{
	StandingSprintSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetCrouchedWalkSpeedMultiplier(float Multiplier)
{
	CrouchedWalkSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetCrouchedAimingSpeedMultiplier(float Multiplier)
{
	CrouchedAimingSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetCrouchedCombatSpeedMultiplier(float Multiplier)
{
	CrouchedCombatSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetCrouchedRunSpeedMultiplier(float Multiplier)
{
	CrouchedRunSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetCrouchedSprintSpeedMultiplier(float Multiplier)
{
	CrouchedSprintSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetProneWalkSpeedMultiplier(float Multiplier)
{
	ProneWalkSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetProneAimingSpeedMultiplier(float Multiplier)
{
	ProneAimingSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetProneCombatSpeedMultiplier(float Multiplier)
{
	ProneCombatSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetProneRunSpeedMultiplier(float Multiplier)
{
	ProneRunSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetProneSprintSpeedMultiplier(float Multiplier)
{
	ProneSprintSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetClimbingWalkSpeedMultiplier(float Multiplier)
{
	ClimbingWalkSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetClimbingAimingSpeedMultiplier(float Multiplier)
{
	ClimbingAimingSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetClimbingCombatSpeedMultiplier(float Multiplier)
{
	ClimbingCombatSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetClimbingRunSpeedMultiplier(float Multiplier)
{
	ClimbingRunSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetClimbingSprintSpeedMultiplier(float Multiplier)
{
	ClimbingSprintSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetSwimmingWalkSpeedMultiplier(float Multiplier)
{
	SwimmingWalkSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetSwimmingAimingSpeedMultiplier(float Multiplier)
{
	SwimmingAimingSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetSwimmingCombatSpeedMultiplier(float Multiplier)
{
	SwimmingCombatSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetSwimmingRunSpeedMultiplier(float Multiplier)
{
	SwimmingRunSpeedMultiplier = Multiplier;
}

void UALSXTCharacterMovementComponent::SetSwimmingSprintSpeedMultiplier(float Multiplier)
{
	SwimmingSprintSpeedMultiplier = Multiplier;
}