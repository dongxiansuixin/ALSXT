#include "AbilitySystem/AttributeSets/ALSXTAbilitiesAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

float UALSXTAbilitiesAttributeSet::COOLDOWN_MULTIPLIER_MIN = 0.1f;
float UALSXTAbilitiesAttributeSet::COOLDOWN_MULTIPLIER_MAX = 2.f;

float UALSXTAbilitiesAttributeSet::COST_MULTIPLIER_MIN = 0.1f;
float UALSXTAbilitiesAttributeSet::COST_MULTIPLIER_MAX = 2.f;

UALSXTAbilitiesAttributeSet::UALSXTAbilitiesAttributeSet()
{
	InitCooldownMultiplier(1.f);
	InitCostMultiplier(1.f);
}

void UALSXTAbilitiesAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UALSXTAbilitiesAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UALSXTAbilitiesAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UALSXTAbilitiesAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetCostMultiplierAttribute())
	{
		NewValue = FMath::Clamp(NewValue, COST_MULTIPLIER_MIN, COST_MULTIPLIER_MAX);
		return;
	}

	if (Attribute == GetCooldownMultiplierAttribute())
	{
		NewValue = FMath::Clamp(NewValue, COOLDOWN_MULTIPLIER_MIN, COOLDOWN_MULTIPLIER_MAX);
		return;
	}
}

void UALSXTAbilitiesAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_OwnerOnly;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTAbilitiesAttributeSet, CooldownMultiplier, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTAbilitiesAttributeSet, CostMultiplier, Params);
}

void UALSXTAbilitiesAttributeSet::OnRep_CooldownMultiplier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTAbilitiesAttributeSet, CooldownMultiplier, OldValue);
}

void UALSXTAbilitiesAttributeSet::OnRep_CostMultiplier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTAbilitiesAttributeSet, CostMultiplier, OldValue);
}