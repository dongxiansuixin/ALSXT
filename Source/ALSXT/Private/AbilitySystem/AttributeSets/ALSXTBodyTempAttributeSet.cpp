// MIT


#include "AbilitySystem/AttributeSets/ALSXTBodyTempAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Data/ALSXTGASGameplayTags.h"
#include "Net/UnrealNetwork.h"

UALSXTBodyTempAttributeSet::UALSXTBodyTempAttributeSet()
{
	MaximumBodyTemp = 1.0f;
	CurrentBodyTemp = 1.0f;
	BodyTempRegeneration = 0.0f;
	Bleeding = 0.f;
	BleedHealing = 0.f;
}

void UALSXTBodyTempAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTBodyTempAttributeSet, CurrentBodyTemp, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTBodyTempAttributeSet, MaximumBodyTemp, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTBodyTempAttributeSet, Bleeding, Params);

	// Only Owner
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTBodyTempAttributeSet, BodyTempRegeneration, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTBodyTempAttributeSet, BleedHealing, Params);
}

void UALSXTBodyTempAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
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

void UALSXTBodyTempAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Store a local copy of the amount of Damage done and clear the Damage attribute.
		const float LocalDamageDone = GetDamage();

		SetDamage(0.f);
	
		if (LocalDamageDone > 0.0f)
		{
			// Apply the BodyTemp change and then clamp it.
			const float NewBodyTemp = GetCurrentBodyTemp() - LocalDamageDone;

			SetCurrentBodyTemp(FMath::Clamp(NewBodyTemp, 0.0f, GetMaximumBodyTemp()));
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
			// Apply the BodyTemp change and then clamp it.
			const float NewBodyTemp = GetCurrentBodyTemp() + LocalHealingDone;

			SetCurrentBodyTemp(FMath::Clamp(NewBodyTemp, 0.0f, GetMaximumBodyTemp()));
		}
		return;
	}

	if (Data.EvaluatedData.Attribute == GetBodyTempRegenerationAttribute())
	{
		SetBodyTempRegeneration(FMath::Clamp(GetBodyTempRegeneration(), 0.0f, GetMaximumBodyTemp()));
		return;
	}
}

void UALSXTBodyTempAttributeSet::OnRep_CurrentBodyTemp(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTBodyTempAttributeSet, CurrentBodyTemp, OldValue);
}

void UALSXTBodyTempAttributeSet::OnRep_MaximumBodyTemp(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTBodyTempAttributeSet, MaximumBodyTemp, OldValue);
}

void UALSXTBodyTempAttributeSet::OnRep_BodyTempRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTBodyTempAttributeSet, BodyTempRegeneration, OldValue);
}

void UALSXTBodyTempAttributeSet::OnRep_Bleeding(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTBodyTempAttributeSet, Bleeding, OldValue);
}

void UALSXTBodyTempAttributeSet::OnRep_BleedHealing(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTBodyTempAttributeSet, BleedHealing, OldValue);
}

void UALSXTBodyTempAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetCurrentBodyTempAttribute())
	{
		CheckMaxReachedForAttribute(MaximumBodyTemp, ALSXTGASGameplayTags::State::TAG_State_Max_BodyTemp.GetTag(), NewValue);
		return;
	}
	
	if (Attribute == GetBleedingAttribute())
	{
		CheckStatusTagForAttribute(ALSXTGASGameplayTags::Statuses::TAG_Debuff_Bleeding, NewValue, OldValue);
		return;
	}

	if (Attribute == GetMaximumBodyTempAttribute())
	{
		AdjustAttributeForMaxChange(GetCurrentBodyTempAttribute(), OldValue, NewValue);
		return;
	}
}

void UALSXTBodyTempAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UALSXTBodyTempAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetMaximumBodyTempAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.f);
		return;
	}
	if (Attribute == GetCurrentBodyTempAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaximumBodyTemp());
		return;
	}
	if (Attribute == GetBleedingAttribute() || Attribute == GetBleedHealingAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
		return;
	}
}


