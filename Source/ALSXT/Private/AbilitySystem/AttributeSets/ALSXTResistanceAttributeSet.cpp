// MIT


#include "AbilitySystem/AttributeSets/ALSXTResistanceAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

float UALSXTResistanceAttributeSet::RESISTANCE_BASE = 100.f; 
float UALSXTResistanceAttributeSet::RESISTANCE_MAX = 200.f; // 3 times the base armor.
float UALSXTResistanceAttributeSet::RESISTANCE_MIN = -75.f; // Up to 1/4 of the base armor.

UALSXTResistanceAttributeSet::UALSXTResistanceAttributeSet()
{
	Resistance = 0.0f;
}

void UALSXTResistanceAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UALSXTResistanceAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);
	if (Attribute == GetResistanceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, RESISTANCE_MIN, RESISTANCE_MAX);
		return;
	}
}

void UALSXTResistanceAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_OwnerOnly;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTResistanceAttributeSet, Resistance, Params);
}

void UALSXTResistanceAttributeSet::OnRep_Resistance(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTResistanceAttributeSet, Resistance, OldValue);
}