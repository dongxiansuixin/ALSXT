// MIT


#include "AbilitySystem/AttributeSets/ALSXTWeightAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

float UALSXTWeightAttributeSet::Weight_BASE = 100.f; 
float UALSXTWeightAttributeSet::Weight_MAX = 200.f; // 3 times the base armor.
float UALSXTWeightAttributeSet::Weight_MIN = -75.f; // Up to 1/4 of the base armor.

UALSXTWeightAttributeSet::UALSXTWeightAttributeSet()
{
	Weight = 0.0f;
}

void UALSXTWeightAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UALSXTWeightAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);
	if (Attribute == GetWeightAttribute())
	{
		NewValue = FMath::Clamp(NewValue, Weight_MIN, Weight_MAX);
		return;
	}
}

void UALSXTWeightAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_OwnerOnly;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTWeightAttributeSet, Weight, Params);
}

void UALSXTWeightAttributeSet::OnRep_Weight(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTWeightAttributeSet, Weight, OldValue);
}