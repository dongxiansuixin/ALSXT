// MIT


#include "AbilitySystem/AttributeSets/ALSXTStaminaAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Data/ALSXTGASGameplayTags.h"
#include "Net/UnrealNetwork.h"

UALSXTStaminaAttributeSet::UALSXTStaminaAttributeSet()
{
	MaximumStamina = 1.0f;
	CurrentStamina = 1.0f;
	StaminaRegeneration = 0.0f;
}

void UALSXTStaminaAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,	float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentStaminaAttribute())
	{
		CheckMaxReachedForAttribute(MaximumStamina, ALSXTGASGameplayTags::State::TAG_State_Max_Stamina.GetTag(), NewValue);
		return;
	}

	if (Attribute == GetMaximumStaminaAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentStaminaAttribute(), OldValue, NewValue);
		return;
	}
}

void UALSXTStaminaAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);
	
	if (Attribute == GetCurrentStaminaAttribute())
	{
		// This should be removed in favor of another method, as we're modifying 2 times the current stamina. (One right before post, one right after (here).
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumStamina());
		return;
	}

	if (Attribute == GetStaminaRegenerationAttribute())
	{
		NewValue = FMath::Max(0.f, NewValue);
		return;
	}
}

void UALSXTStaminaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTStaminaAttributeSet, CurrentStamina, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTStaminaAttributeSet, MaximumStamina, Params);

	// Owner Only
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTStaminaAttributeSet, StaminaRegeneration, Params);
}

void UALSXTStaminaAttributeSet::OnRep_CurrentStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTStaminaAttributeSet, CurrentStamina, OldValue);
}

void UALSXTStaminaAttributeSet::OnRep_MaximumStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTStaminaAttributeSet, MaximumStamina, OldValue);
}

void UALSXTStaminaAttributeSet::OnRep_StaminaRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTStaminaAttributeSet, StaminaRegeneration, OldValue);
}