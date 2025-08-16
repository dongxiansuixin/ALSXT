// MIT

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ALSXTAttributeSetBase.h"
#include "AbilitySystem/AttributeSets/ALSXTAttributeSetBase.h"
#include "AbilitySystem/Data/ALSXTAbilitySystemData.h"
#include "ALSXTHoldBreathAttributeSet.generated.h"

// Contains Attributes related to HoldBreath. Any Character that takes damage will need this Attribute Set.
//
// Contents:
//
// Current HoldBreath - How much HoldBreath the Character has at this moment.
// Maximum HoldBreath - The maximum amount of HoldBreath the Character can have.
// HoldBreath Regeneration - How much HoldBreath is gained per period of Regeneration.
//
// Damage - A meta Attribute that negatively changes the value of HoldBreath.
// Healing - A meta Attribute that positively changes the value of HoldBreath.

UCLASS()
class ALSXT_API UALSXTHoldBreathAttributeSet : public UALSXTAttributeSetBase
{
	GENERATED_BODY()
	
	public:
	UALSXTHoldBreathAttributeSet();
	
	// Attribute Set Overrides.
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Set Attributes to replicate.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Used to create a local copy of Damage which is then subtracted from Current HoldBreath.
	UPROPERTY(BlueprintReadOnly, Category = "HoldBreath Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UALSXTHoldBreathAttributeSet, Damage)

	// Used to create a local copy of Healing which is then added to Current HoldBreath.
	UPROPERTY(BlueprintReadOnly, Category = "HoldBreath Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UALSXTHoldBreathAttributeSet, Healing)

	// Used to create a local copy of Bleed which is then added to Bleeding.
	UPROPERTY(BlueprintReadOnly, Category = "HoldBreath Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData ReceivedBleed;
	ATTRIBUTE_ACCESSORS(UALSXTHoldBreathAttributeSet, ReceivedBleed)

	// Used to create a local copy of Direct Damage which is then added to Current HoldBreath.
	UPROPERTY(BlueprintReadOnly, Category = "HoldBreath Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData ReceivedDirectDamage;
	ATTRIBUTE_ACCESSORS(UALSXTHoldBreathAttributeSet, ReceivedDirectDamage)
	
	// Holds the current value for HoldBreath.
	UPROPERTY(BlueprintReadOnly, Category = "HoldBreath Attribute Set", ReplicatedUsing = OnRep_CurrentHoldBreath)
	FGameplayAttributeData CurrentHoldBreath;
	ATTRIBUTE_ACCESSORS(UALSXTHoldBreathAttributeSet, CurrentHoldBreath)

	// Holds the value for Maximum HoldBreath.
	UPROPERTY(BlueprintReadOnly, Category = "HoldBreath Attribute Set", ReplicatedUsing = OnRep_MaximumHoldBreath)
	FGameplayAttributeData MaximumHoldBreath;
	ATTRIBUTE_ACCESSORS(UALSXTHoldBreathAttributeSet, MaximumHoldBreath)

	// Holds the value for HoldBreath Regeneration.
	UPROPERTY(BlueprintReadOnly, Category = "HoldBreath Attribute Set", ReplicatedUsing = OnRep_HoldBreathRegeneration)
	FGameplayAttributeData HoldBreathRegeneration;
	ATTRIBUTE_ACCESSORS(UALSXTHoldBreathAttributeSet, HoldBreathRegeneration)

	// Holds the current bleeding amount
	UPROPERTY(BlueprintReadOnly, Category = "HoldBreath Attribute Set", ReplicatedUsing = OnRep_Bleeding)
	FGameplayAttributeData Bleeding;
	ATTRIBUTE_ACCESSORS(UALSXTHoldBreathAttributeSet, Bleeding)

	// Holds the current bleed healing rate
	UPROPERTY(BlueprintReadOnly, Category = "HoldBreath Attribute Set", ReplicatedUsing = OnRep_BleedHealing)
	FGameplayAttributeData BleedHealing;
	ATTRIBUTE_ACCESSORS(UALSXTHoldBreathAttributeSet, BleedHealing)

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayAttribute, FCustomAttributeMaxValue> AttributeMaxValue;
	
	UFUNCTION()
	virtual void OnRep_CurrentHoldBreath(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaximumHoldBreath(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_HoldBreathRegeneration(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Bleeding(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_BleedHealing(const FGameplayAttributeData& OldValue);
	
	
};
