// MIT


#include "AbilitySystem/AttributeSets/ALSXTEnergyAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Data/ALSXTGASGameplayTags.h"
#include "Net/UnrealNetwork.h"

UALSXTEnergyAttributeSet::UALSXTEnergyAttributeSet()
{
	MaximumEnergy = 1.0f;
	CurrentEnergy = 1.0f;
	EnergyRegeneration = 0.0f;
	Bleeding = 0.f;
	BleedHealing = 0.f;
}

void UALSXTEnergyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTEnergyAttributeSet, CurrentEnergy, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTEnergyAttributeSet, MaximumEnergy, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTEnergyAttributeSet, Bleeding, Params);

	// Only Owner
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTEnergyAttributeSet, EnergyRegeneration, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTEnergyAttributeSet, BleedHealing, Params);
}

void UALSXTEnergyAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
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

void UALSXTEnergyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Store a local copy of the amount of Damage done and clear the Damage attribute.
		const float LocalDamageDone = GetDamage();

		SetDamage(0.f);
	
		if (LocalDamageDone > 0.0f)
		{
			// Apply the Energy change and then clamp it.
			const float NewEnergy = GetCurrentEnergy() - LocalDamageDone;

			SetCurrentEnergy(FMath::Clamp(NewEnergy, 0.0f, GetMaximumEnergy()));
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
			// Apply the Energy change and then clamp it.
			const float NewEnergy = GetCurrentEnergy() + LocalHealingDone;

			SetCurrentEnergy(FMath::Clamp(NewEnergy, 0.0f, GetMaximumEnergy()));
		}
		return;
	}

	if (Data.EvaluatedData.Attribute == GetEnergyRegenerationAttribute())
	{
		SetEnergyRegeneration(FMath::Clamp(GetEnergyRegeneration(), 0.0f, GetMaximumEnergy()));
		return;
	}
}

void UALSXTEnergyAttributeSet::OnRep_CurrentEnergy(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTEnergyAttributeSet, CurrentEnergy, OldValue);
}

void UALSXTEnergyAttributeSet::OnRep_MaximumEnergy(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTEnergyAttributeSet, MaximumEnergy, OldValue);
}

void UALSXTEnergyAttributeSet::OnRep_EnergyRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTEnergyAttributeSet, EnergyRegeneration, OldValue);
}

void UALSXTEnergyAttributeSet::OnRep_Bleeding(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTEnergyAttributeSet, Bleeding, OldValue);
}

void UALSXTEnergyAttributeSet::OnRep_BleedHealing(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTEnergyAttributeSet, BleedHealing, OldValue);
}

void UALSXTEnergyAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentEnergyAttribute())
	{
		CheckMaxReachedForAttribute(MaximumEnergy, ALSXTGASGameplayTags::State::TAG_State_Max_Energy.GetTag(), NewValue);
		return;
	}
	
	if (Attribute == GetBleedingAttribute())
	{
		CheckStatusTagForAttribute(ALSXTGASGameplayTags::Statuses::TAG_Debuff_Bleeding, NewValue, OldValue);
		return;
	}

	if (Attribute == GetMaximumEnergyAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentEnergyAttribute(), OldValue, NewValue);
		return;
	}
}

void UALSXTEnergyAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UALSXTEnergyAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetMaximumEnergyAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.f);
		return;
	}
	if (Attribute == GetCurrentEnergyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumEnergy());
		return;
	}
	if (Attribute == GetBleedingAttribute() || Attribute == GetBleedHealingAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
		return;
	}
}


