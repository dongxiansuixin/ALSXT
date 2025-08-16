// MIT

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ALSXTAttributeSetBase.h"
#include "AbilitySystem/AttributeSets/ALSXTAttributeSetBase.h"
#include "AbilitySystem/Data/ALSXTAbilitySystemData.h"
#include "ALSXTBloodAttributeSet.generated.h"

// Contains Attributes related to Blood. Any Character that takes damage will need this Attribute Set.
//
// Contents:
//
// Current Blood - How much Blood the Character has at this moment.
// Maximum Blood - The maximum amount of Blood the Character can have.
// Blood Regeneration - How much Blood is gained per period of Regeneration.
//
// Damage - A meta Attribute that negatively changes the value of Blood.
// Healing - A meta Attribute that positively changes the value of Blood.

UCLASS()
class ALSXT_API UALSXTBloodAttributeSet : public UALSXTAttributeSetBase
{
	GENERATED_BODY()
	
	public:
	UALSXTBloodAttributeSet();
	
	// Attribute Set Overrides.
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Set Attributes to replicate.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Used to create a local copy of Damage which is then subtracted from Current Blood.
	UPROPERTY(BlueprintReadOnly, Category = "Blood Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UALSXTBloodAttributeSet, Damage)

	// Used to create a local copy of Healing which is then added to Current Blood.
	UPROPERTY(BlueprintReadOnly, Category = "Blood Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UALSXTBloodAttributeSet, Healing)

	// Used to create a local copy of Bleed which is then added to Bleeding.
	UPROPERTY(BlueprintReadOnly, Category = "Blood Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData ReceivedBleed;
	ATTRIBUTE_ACCESSORS(UALSXTBloodAttributeSet, ReceivedBleed)

	// Used to create a local copy of Direct Damage which is then added to Current Blood.
	UPROPERTY(BlueprintReadOnly, Category = "Blood Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData ReceivedDirectDamage;
	ATTRIBUTE_ACCESSORS(UALSXTBloodAttributeSet, ReceivedDirectDamage)
	
	// Holds the current value for Blood.
	UPROPERTY(BlueprintReadOnly, Category = "Blood Attribute Set", ReplicatedUsing = OnRep_CurrentBlood)
	FGameplayAttributeData CurrentBlood;
	ATTRIBUTE_ACCESSORS(UALSXTBloodAttributeSet, CurrentBlood)

	// Holds the value for Maximum Blood.
	UPROPERTY(BlueprintReadOnly, Category = "Blood Attribute Set", ReplicatedUsing = OnRep_MaximumBlood)
	FGameplayAttributeData MaximumBlood;
	ATTRIBUTE_ACCESSORS(UALSXTBloodAttributeSet, MaximumBlood)

	// Holds the value for Blood Regeneration.
	UPROPERTY(BlueprintReadOnly, Category = "Blood Attribute Set", ReplicatedUsing = OnRep_BloodRegeneration)
	FGameplayAttributeData BloodRegeneration;
	ATTRIBUTE_ACCESSORS(UALSXTBloodAttributeSet, BloodRegeneration)

	// Holds the current bleeding amount
	UPROPERTY(BlueprintReadOnly, Category = "Blood Attribute Set", ReplicatedUsing = OnRep_Bleeding)
	FGameplayAttributeData Bleeding;
	ATTRIBUTE_ACCESSORS(UALSXTBloodAttributeSet, Bleeding)

	// Holds the current bleed healing rate
	UPROPERTY(BlueprintReadOnly, Category = "Blood Attribute Set", ReplicatedUsing = OnRep_BleedHealing)
	FGameplayAttributeData BleedHealing;
	ATTRIBUTE_ACCESSORS(UALSXTBloodAttributeSet, BleedHealing)

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayAttribute, FCustomAttributeMaxValue> AttributeMaxValue;
	
	UFUNCTION()
	virtual void OnRep_CurrentBlood(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaximumBlood(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_BloodRegeneration(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Bleeding(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_BleedHealing(const FGameplayAttributeData& OldValue);
	
	
};
