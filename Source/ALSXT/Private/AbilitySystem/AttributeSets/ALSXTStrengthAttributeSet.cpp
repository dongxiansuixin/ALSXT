// MIT


#include "AbilitySystem/AttributeSets/ALSXTStrengthAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Data/ALSXTGASGameplayTags.h"
#include "Net/UnrealNetwork.h"

UALSXTStrengthAttributeSet::UALSXTStrengthAttributeSet()
{
	MaximumStrength = 1.0f;
	CurrentStrength = 1.0f;
	StrengthRegeneration = 0.0f;
	Bleeding = 0.f;
	BleedHealing = 0.f;
}

void UALSXTStrengthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTStrengthAttributeSet, CurrentStrength, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTStrengthAttributeSet, MaximumStrength, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTStrengthAttributeSet, Bleeding, Params);

	// Only Owner
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTStrengthAttributeSet, StrengthRegeneration, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTStrengthAttributeSet, BleedHealing, Params);
}

void UALSXTStrengthAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
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

void UALSXTStrengthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Store a local copy of the amount of Damage done and clear the Damage attribute.
		const float LocalDamageDone = GetDamage();

		SetDamage(0.f);
	
		if (LocalDamageDone > 0.0f)
		{
			// Apply the Strength change and then clamp it.
			const float NewStrength = GetCurrentStrength() - LocalDamageDone;

			SetCurrentStrength(FMath::Clamp(NewStrength, 0.0f, GetMaximumStrength()));
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
			// Apply the Strength change and then clamp it.
			const float NewStrength = GetCurrentStrength() + LocalHealingDone;

			SetCurrentStrength(FMath::Clamp(NewStrength, 0.0f, GetMaximumStrength()));
		}
		return;
	}

	if (Data.EvaluatedData.Attribute == GetStrengthRegenerationAttribute())
	{
		SetStrengthRegeneration(FMath::Clamp(GetStrengthRegeneration(), 0.0f, GetMaximumStrength()));
		return;
	}
}

void UALSXTStrengthAttributeSet::OnRep_CurrentStrength(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTStrengthAttributeSet, CurrentStrength, OldValue);
}

void UALSXTStrengthAttributeSet::OnRep_MaximumStrength(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTStrengthAttributeSet, MaximumStrength, OldValue);
}

void UALSXTStrengthAttributeSet::OnRep_StrengthRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTStrengthAttributeSet, StrengthRegeneration, OldValue);
}

void UALSXTStrengthAttributeSet::OnRep_Bleeding(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTStrengthAttributeSet, Bleeding, OldValue);
}

void UALSXTStrengthAttributeSet::OnRep_BleedHealing(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTStrengthAttributeSet, BleedHealing, OldValue);
}

void UALSXTStrengthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentStrengthAttribute())
	{
		CheckMaxReachedForAttribute(MaximumStrength, ALSXTGASGameplayTags::State::TAG_State_Max_Strength.GetTag(), NewValue);
		return;
	}
	
	if (Attribute == GetBleedingAttribute())
	{
		CheckStatusTagForAttribute(ALSXTGASGameplayTags::Statuses::TAG_Debuff_Bleeding, NewValue, OldValue);
		return;
	}

	if (Attribute == GetMaximumStrengthAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentStrengthAttribute(), OldValue, NewValue);
		return;
	}
}

void UALSXTStrengthAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UALSXTStrengthAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetMaximumStrengthAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.f);
		return;
	}
	if (Attribute == GetCurrentStrengthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumStrength());
		return;
	}
	if (Attribute == GetBleedingAttribute() || Attribute == GetBleedHealingAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
		return;
	}
}


