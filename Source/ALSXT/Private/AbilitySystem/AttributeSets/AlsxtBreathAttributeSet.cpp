// MIT


#include "AbilitySystem/AttributeSets/AlsxtBreathAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Data/AlsxtGasGameplayTags.h"
#include "Net/UnrealNetwork.h"

UAlsxtBreathAttributeSet::UAlsxtBreathAttributeSet()
{
	MaximumBreathRate = 1.0f;
	CurrentBreathRate = 1.0f;
	CurrentBreathRegeneration = 0.0f;
	MaxBreathRegeneration = 0.0f;
}

void UAlsxtBreathAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,	float NewValue)
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

	if (Attribute == GetCurrentBreathRateAttribute())
	{
		CheckMaxReachedForAttribute(MaxBreathRegeneration, ALSXTGASGameplayTags::State::TAG_State_Max_BreathRegen.GetTag(), NewValue);
		return;
	}

	if (Attribute == GetMaximumBreathRateAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentBreathRegenerationAttribute(), OldValue, NewValue);
		return;
	}
}

void UAlsxtBreathAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);
	
	if (Attribute == GetCurrentBreathRateAttribute())
	{
		// This should be removed in favor of another method, as we're modifying 2 times the current Breath. (One right before post, one right after (here).
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumBreathRate());
		return;
	}

	if (Attribute == GetCurrentBreathRegenerationAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxBreathRegeneration());
		// NewValue = FMath::Max(0.f, NewValue);
		return;
	}
}

void UAlsxtBreathAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtBreathAttributeSet, CurrentBreathRate, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtBreathAttributeSet, MaximumBreathRate, Params);

	// Owner Only
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtBreathAttributeSet, CurrentBreathRegeneration, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtBreathAttributeSet, MaxBreathRegeneration, Params);
}

void UAlsxtBreathAttributeSet::OnRep_CurrentBreathRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtBreathAttributeSet, CurrentBreathRate, OldValue);
}

void UAlsxtBreathAttributeSet::OnRep_MaximumBreathRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtBreathAttributeSet, MaximumBreathRate, OldValue);
}

void UAlsxtBreathAttributeSet::OnRep_CurrentBreathRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtBreathAttributeSet, CurrentBreathRegeneration, OldValue);
}

void UAlsxtBreathAttributeSet::OnRep_MaxBreathRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtBreathAttributeSet, MaxBreathRegeneration, OldValue);
}