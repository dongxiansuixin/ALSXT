// MIT


#include "AbilitySystem/AttributeSets/ALSXTNutritionAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Data/ALSXTGASGameplayTags.h"
#include "Net/UnrealNetwork.h"

UALSXTNutritionAttributeSet::UALSXTNutritionAttributeSet()
{
	MaximumNutrition = 1.0f;
	CurrentNutrition = 1.0f;
	NutritionRegeneration = 0.0f;
	Bleeding = 0.f;
	BleedHealing = 0.f;
}

void UALSXTNutritionAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTNutritionAttributeSet, CurrentNutrition, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTNutritionAttributeSet, MaximumNutrition, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTNutritionAttributeSet, Bleeding, Params);

	// Only Owner
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTNutritionAttributeSet, NutritionRegeneration, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTNutritionAttributeSet, BleedHealing, Params);
}

void UALSXTNutritionAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
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

void UALSXTNutritionAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Store a local copy of the amount of Damage done and clear the Damage attribute.
		const float LocalDamageDone = GetDamage();

		SetDamage(0.f);
	
		if (LocalDamageDone > 0.0f)
		{
			// Apply the Nutrition change and then clamp it.
			const float NewNutrition = GetCurrentNutrition() - LocalDamageDone;

			SetCurrentNutrition(FMath::Clamp(NewNutrition, 0.0f, GetMaximumNutrition()));
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
			// Apply the Nutrition change and then clamp it.
			const float NewNutrition = GetCurrentNutrition() + LocalHealingDone;

			SetCurrentNutrition(FMath::Clamp(NewNutrition, 0.0f, GetMaximumNutrition()));
		}
		return;
	}

	if (Data.EvaluatedData.Attribute == GetNutritionRegenerationAttribute())
	{
		SetNutritionRegeneration(FMath::Clamp(GetNutritionRegeneration(), 0.0f, GetMaximumNutrition()));
		return;
	}
}

void UALSXTNutritionAttributeSet::OnRep_CurrentNutrition(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTNutritionAttributeSet, CurrentNutrition, OldValue);
}

void UALSXTNutritionAttributeSet::OnRep_MaximumNutrition(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTNutritionAttributeSet, MaximumNutrition, OldValue);
}

void UALSXTNutritionAttributeSet::OnRep_NutritionRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTNutritionAttributeSet, NutritionRegeneration, OldValue);
}

void UALSXTNutritionAttributeSet::OnRep_Bleeding(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTNutritionAttributeSet, Bleeding, OldValue);
}

void UALSXTNutritionAttributeSet::OnRep_BleedHealing(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTNutritionAttributeSet, BleedHealing, OldValue);
}

void UALSXTNutritionAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentNutritionAttribute())
	{
		CheckMaxReachedForAttribute(MaximumNutrition, ALSXTGASGameplayTags::State::TAG_State_Max_Nutrition.GetTag(), NewValue);
		return;
	}
	
	if (Attribute == GetBleedingAttribute())
	{
		CheckStatusTagForAttribute(ALSXTGASGameplayTags::Statuses::TAG_Debuff_Bleeding, NewValue, OldValue);
		return;
	}

	if (Attribute == GetMaximumNutritionAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentNutritionAttribute(), OldValue, NewValue);
		return;
	}
}

void UALSXTNutritionAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UALSXTNutritionAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetMaximumNutritionAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.f);
		return;
	}
	if (Attribute == GetCurrentNutritionAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumNutrition());
		return;
	}
	if (Attribute == GetBleedingAttribute() || Attribute == GetBleedHealingAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
		return;
	}
}


