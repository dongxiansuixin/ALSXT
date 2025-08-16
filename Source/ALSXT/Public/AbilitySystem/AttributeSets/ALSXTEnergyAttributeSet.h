// MIT

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ALSXTAttributeSetBase.h"
#include "AbilitySystem/AttributeSets/ALSXTAttributeSetBase.h"
#include "AbilitySystem/Data/ALSXTAbilitySystemData.h"
#include "ALSXTEnergyAttributeSet.generated.h"

// Contains Attributes related to Energy. Any Character that takes damage will need this Attribute Set.
//
// Contents:
//
// Current Energy - How much Energy the Character has at this moment.
// Maximum Energy - The maximum amount of Energy the Character can have.
// Energy Regeneration - How much Energy is gained per period of Regeneration.
//
// Damage - A meta Attribute that negatively changes the value of Energy.
// Healing - A meta Attribute that positively changes the value of Energy.

UCLASS()
class ALSXT_API UALSXTEnergyAttributeSet : public UALSXTAttributeSetBase
{
	GENERATED_BODY()
	
	public:
	UALSXTEnergyAttributeSet();
	
	// Attribute Set Overrides.
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Set Attributes to replicate.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Used to create a local copy of Damage which is then subtracted from Current Energy.
	UPROPERTY(BlueprintReadOnly, Category = "Energy Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UALSXTEnergyAttributeSet, Damage)

	// Used to create a local copy of Healing which is then added to Current Energy.
	UPROPERTY(BlueprintReadOnly, Category = "Energy Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UALSXTEnergyAttributeSet, Healing)

	// Used to create a local copy of Bleed which is then added to Bleeding.
	UPROPERTY(BlueprintReadOnly, Category = "Energy Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData ReceivedBleed;
	ATTRIBUTE_ACCESSORS(UALSXTEnergyAttributeSet, ReceivedBleed)

	// Used to create a local copy of Direct Damage which is then added to Current Energy.
	UPROPERTY(BlueprintReadOnly, Category = "Energy Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData ReceivedDirectDamage;
	ATTRIBUTE_ACCESSORS(UALSXTEnergyAttributeSet, ReceivedDirectDamage)
	
	// Holds the current value for Energy.
	UPROPERTY(BlueprintReadOnly, Category = "Energy Attribute Set", ReplicatedUsing = OnRep_CurrentEnergy)
	FGameplayAttributeData CurrentEnergy;
	ATTRIBUTE_ACCESSORS(UALSXTEnergyAttributeSet, CurrentEnergy)

	// Holds the value for Maximum Energy.
	UPROPERTY(BlueprintReadOnly, Category = "Energy Attribute Set", ReplicatedUsing = OnRep_MaximumEnergy)
	FGameplayAttributeData MaximumEnergy;
	ATTRIBUTE_ACCESSORS(UALSXTEnergyAttributeSet, MaximumEnergy)

	// Holds the value for Energy Regeneration.
	UPROPERTY(BlueprintReadOnly, Category = "Energy Attribute Set", ReplicatedUsing = OnRep_EnergyRegeneration)
	FGameplayAttributeData EnergyRegeneration;
	ATTRIBUTE_ACCESSORS(UALSXTEnergyAttributeSet, EnergyRegeneration)

	// Holds the current bleeding amount
	UPROPERTY(BlueprintReadOnly, Category = "Energy Attribute Set", ReplicatedUsing = OnRep_Bleeding)
	FGameplayAttributeData Bleeding;
	ATTRIBUTE_ACCESSORS(UALSXTEnergyAttributeSet, Bleeding)

	// Holds the current bleed healing rate
	UPROPERTY(BlueprintReadOnly, Category = "Energy Attribute Set", ReplicatedUsing = OnRep_BleedHealing)
	FGameplayAttributeData BleedHealing;
	ATTRIBUTE_ACCESSORS(UALSXTEnergyAttributeSet, BleedHealing)

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayAttribute, FCustomAttributeMaxValue> AttributeMaxValue;
	
	UFUNCTION()
	virtual void OnRep_CurrentEnergy(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaximumEnergy(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_EnergyRegeneration(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Bleeding(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_BleedHealing(const FGameplayAttributeData& OldValue);
	
	
};
