// MIT


#include "AbilitySystem/AttributeSets/AlsxtStaminaAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Data/AlsxtGasGameplayTags.h"
#include "Net/UnrealNetwork.h"

UAlsxtStaminaAttributeSet::UAlsxtStaminaAttributeSet()
{
	MaxStamina = 1.0f;
	CurrentStamina = 1.0f;
	CurrentStaminaRegen = 0.0f;
	MaxStaminaRegen = 0.0f;
}

void UAlsxtStaminaAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentStaminaAttribute())
	{
		CheckMaxReachedForAttribute(MaxStamina, ALSXTGASGameplayTags::State::TAG_State_Max_Stamina.GetTag(), NewValue);
		return;
	}

	if (Attribute == GetMaxStaminaAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentStaminaAttribute(), OldValue, NewValue);
		return;
	}
}

void UAlsxtStaminaAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttributes(Attribute, NewValue);
	
	if (Attribute == GetCurrentStaminaAttribute())
	{
		// This should be removed in favor of another method, as we're modifying 2 times the current stamina. (One right before post, one right after (here).
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
		return;
	}

	if (Attribute == GetCurrentStaminaRegenAttribute())
	{
		NewValue = FMath::Max(0.f, NewValue);
		return;
	}
}

void UAlsxtStaminaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	// Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtStaminaAttributeSet, CurrentStamina, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtStaminaAttributeSet, MaxStamina, Params);

	// Owner Only
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtStaminaAttributeSet, CurrentStaminaRegen, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtStaminaAttributeSet, MaxStaminaRegen, Params);
}

void UAlsxtStaminaAttributeSet::OnRep_CurrentStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtStaminaAttributeSet, CurrentStamina, OldValue);
}

void UAlsxtStaminaAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtStaminaAttributeSet, MaxStamina, OldValue);
}

void UAlsxtStaminaAttributeSet::OnRep_CurrentStaminaRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtStaminaAttributeSet, CurrentStaminaRegen, OldValue);
}

void UAlsxtStaminaAttributeSet::OnRep_MaxStaminaRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtStaminaAttributeSet, MaxStaminaRegen, OldValue);
}