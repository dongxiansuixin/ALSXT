// MIT


#include "AbilitySystem/AttributeSets/ALSXTEncumbranceAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

float UALSXTEncumbranceAttributeSet::Encumbrance_BASE = 100.f; 
float UALSXTEncumbranceAttributeSet::Encumbrance_MAX = 200.f; // 3 times the base armor.
float UALSXTEncumbranceAttributeSet::Encumbrance_MIN = -75.f; // Up to 1/4 of the base armor.

UALSXTEncumbranceAttributeSet::UALSXTEncumbranceAttributeSet()
{
	Encumbrance = 0.0f;
}

void UALSXTEncumbranceAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UALSXTEncumbranceAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);
	if (Attribute == GetEncumbranceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, Encumbrance_MIN, Encumbrance_MAX);
		return;
	}
}

void UALSXTEncumbranceAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_OwnerOnly;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTEncumbranceAttributeSet, Encumbrance, Params);
}

void UALSXTEncumbranceAttributeSet::OnRep_Encumbrance(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTEncumbranceAttributeSet, Encumbrance, OldValue);
}