// MIT

#include "AbilitySystem/AttributeSets/ALSXTMovementAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UALSXTMovementAttributeSet::UALSXTMovementAttributeSet()
{
	MovementSpeedMultiplier = 1.0f;
	MovementAccelerationMultiplier = 1.0f;
}

void UALSXTMovementAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	// Make sure we don't change the base at this is always supposed to return a multiplier. 
	NewValue = 1.f;
}

void UALSXTMovementAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);

	// Make sure 
	NewValue = FMath::Max(NewValue, 0.f);
}

void UALSXTMovementAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_OwnerOnly;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTMovementAttributeSet, MovementSpeedMultiplier, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTMovementAttributeSet, MovementAccelerationMultiplier, Params);
}

void UALSXTMovementAttributeSet::OnRep_MovementSpeedMultiplier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTMovementAttributeSet, MovementSpeedMultiplier, OldValue);
}

void UALSXTMovementAttributeSet::OnRep_MovementAccelerationMultiplier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTMovementAttributeSet, MovementAccelerationMultiplier, OldValue);
}