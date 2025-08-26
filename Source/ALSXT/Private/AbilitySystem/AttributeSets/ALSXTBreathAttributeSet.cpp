// MIT


#include "AbilitySystem/AttributeSets/ALSXTBreathAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Data/ALSXTGASGameplayTags.h"
#include "Net/UnrealNetwork.h"

UALSXTBreathAttributeSet::UALSXTBreathAttributeSet()
{
	MaximumBreathRate = 1.0f;
	CurrentBreathRate = 1.0f;
	BreathRegeneration = 0.0f;
}

void UALSXTBreathAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,	float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentBreathRateAttribute())
	{
		CheckMaxReachedForAttribute(MaximumBreathRate, ALSXTGASGameplayTags::State::TAG_State_Max_Breath.GetTag(), NewValue);
		return;
	}

	if (Attribute == GetMaximumBreathRateAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentBreathRateAttribute(), OldValue, NewValue);
		return;
	}
}

void UALSXTBreathAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);
	
	if (Attribute == GetCurrentBreathRateAttribute())
	{
		// This should be removed in favor of another method, as we're modifying 2 times the current Breath. (One right before post, one right after (here).
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumBreathRate());
		return;
	}

	if (Attribute == GetBreathRegenerationAttribute())
	{
		NewValue = FMath::Max(0.f, NewValue);
		return;
	}
}

void UALSXTBreathAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTBreathAttributeSet, CurrentBreathRate, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTBreathAttributeSet, MaximumBreathRate, Params);

	// Owner Only
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTBreathAttributeSet, BreathRegeneration, Params);
}

void UALSXTBreathAttributeSet::OnRep_CurrentBreathRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTBreathAttributeSet, CurrentBreathRate, OldValue);
}

void UALSXTBreathAttributeSet::OnRep_MaximumBreathRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTBreathAttributeSet, MaximumBreathRate, OldValue);
}

void UALSXTBreathAttributeSet::OnRep_BreathRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTBreathAttributeSet, BreathRegeneration, OldValue);
}