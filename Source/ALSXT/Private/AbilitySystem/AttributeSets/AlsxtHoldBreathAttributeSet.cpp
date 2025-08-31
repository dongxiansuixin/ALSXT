// MIT


#include "AbilitySystem/AttributeSets/AlsxtHoldBreathAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Data/AlsxtGasGameplayTags.h"
#include "Net/UnrealNetwork.h"

UAlsxtHoldBreathAttributeSet::UAlsxtHoldBreathAttributeSet()
{
	MaximumHoldBreath = 1.0f;
	CurrentHoldBreath = 1.0f;
	HoldBreathRegeneration = 0.0f;
	Bleeding = 0.f;
	BleedHealing = 0.f;
}

void UAlsxtHoldBreathAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtHoldBreathAttributeSet, CurrentHoldBreath, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtHoldBreathAttributeSet, MaximumHoldBreath, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtHoldBreathAttributeSet, Bleeding, Params);

	// Only Owner
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtHoldBreathAttributeSet, HoldBreathRegeneration, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAlsxtHoldBreathAttributeSet, BleedHealing, Params);
}

void UAlsxtHoldBreathAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	// const FCustomAttributeMaxValue* MaximumValue;

	if (const FCustomAttributeMaxValue* MaximumValue = AttributeMaxValue.Find(Attribute))
	{
		// const float Max = MaximumValue->MaxAttribute.IsValid() ? MaximumValue->MaxAttribute.GetNumericValue(this) : MaximumValue->MaxFloat.GetValueAtLevel(0);

		// NewValue = FMath::Clamp(NewValue, 0.f, Max);
		return;
	}
}

void UAlsxtHoldBreathAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Store a local copy of the amount of Damage done and clear the Damage attribute.
		const float LocalDamageDone = GetDamage();

		SetDamage(0.f);
	
		if (LocalDamageDone > 0.0f)
		{
			// Apply the HoldBreath change and then clamp it.
			const float NewHoldBreath = GetCurrentHoldBreath() - LocalDamageDone;

			SetCurrentHoldBreath(FMath::Clamp(NewHoldBreath, 0.0f, GetMaximumHoldBreath()));
		}
		return;
	}

	if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		// Store a local copy of the amount of Healing done and clear the Healing attribute.
		const float LocalHealingDone = GetHealing();

		SetHealing(0.f);
	
		if (LocalHealingDone > 0.0f)
		{
			// Apply the HoldBreath change and then clamp it.
			const float NewHoldBreath = GetCurrentHoldBreath() + LocalHealingDone;

			SetCurrentHoldBreath(FMath::Clamp(NewHoldBreath, 0.0f, GetMaximumHoldBreath()));
		}
		return;
	}

	if (Data.EvaluatedData.Attribute == GetHoldBreathRegenerationAttribute())
	{
		SetHoldBreathRegeneration(FMath::Clamp(GetHoldBreathRegeneration(), 0.0f, GetMaximumHoldBreath()));
		return;
	}
}

void UAlsxtHoldBreathAttributeSet::OnRep_CurrentHoldBreath(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtHoldBreathAttributeSet, CurrentHoldBreath, OldValue);
}

void UAlsxtHoldBreathAttributeSet::OnRep_MaximumHoldBreath(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtHoldBreathAttributeSet, MaximumHoldBreath, OldValue);
}

void UAlsxtHoldBreathAttributeSet::OnRep_HoldBreathRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtHoldBreathAttributeSet, HoldBreathRegeneration, OldValue);
}

void UAlsxtHoldBreathAttributeSet::OnRep_Bleeding(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtHoldBreathAttributeSet, Bleeding, OldValue);
}

void UAlsxtHoldBreathAttributeSet::OnRep_BleedHealing(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAlsxtHoldBreathAttributeSet, BleedHealing, OldValue);
}

void UAlsxtHoldBreathAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentHoldBreathAttribute())
	{
		CheckMaxReachedForAttribute(MaximumHoldBreath, ALSXTGASGameplayTags::State::TAG_State_Max_HoldBreath.GetTag(), NewValue);
		return;
	}
	
	if (Attribute == GetBleedingAttribute())
	{
		CheckStatusTagForAttribute(ALSXTGASGameplayTags::Statuses::TAG_Debuff_Bleeding, NewValue, OldValue);
		return;
	}

	if (Attribute == GetMaximumHoldBreathAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentHoldBreathAttribute(), OldValue, NewValue);
		return;
	}
}

void UAlsxtHoldBreathAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UAlsxtHoldBreathAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetMaximumHoldBreathAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.f);
		return;
	}
	if (Attribute == GetCurrentHoldBreathAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumHoldBreath());
		return;
	}
	if (Attribute == GetBleedingAttribute() || Attribute == GetBleedHealingAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
		return;
	}
}


