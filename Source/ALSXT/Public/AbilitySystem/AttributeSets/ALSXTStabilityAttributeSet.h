// MIT

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ALSXTAttributeSetBase.h"
#include "AbilitySystem/AttributeSets/ALSXTAttributeSetBase.h"
#include "AbilitySystem/Data/ALSXTAbilitySystemData.h"
#include "ALSXTStabilityAttributeSet.generated.h"

// Contains Attributes related to Stability. Any Character that takes damage will need this Attribute Set.
//
// Contents:
//
// Current Stability - How much Stability the Character has at this moment.
// Maximum Stability - The maximum amount of Stability the Character can have.
// Stability Regeneration - How much Stability is gained per period of Regeneration.
//
// Damage - A meta Attribute that negatively changes the value of Stability.
// Healing - A meta Attribute that positively changes the value of Stability.

UCLASS()
class ALSXT_API UALSXTStabilityAttributeSet : public UALSXTAttributeSetBase
{
	GENERATED_BODY()
	
	public:
	UALSXTStabilityAttributeSet();
	
	// Attribute Set Overrides.
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Set Attributes to replicate.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Used to create a local copy of Damage which is then subtracted from Current Stability.
	UPROPERTY(BlueprintReadOnly, Category = "Stability Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UALSXTStabilityAttributeSet, Damage)

	// Used to create a local copy of Healing which is then added to Current Stability.
	UPROPERTY(BlueprintReadOnly, Category = "Stability Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UALSXTStabilityAttributeSet, Healing)

	// Used to create a local copy of Bleed which is then added to Bleeding.
	UPROPERTY(BlueprintReadOnly, Category = "Stability Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData ReceivedBleed;
	ATTRIBUTE_ACCESSORS(UALSXTStabilityAttributeSet, ReceivedBleed)

	// Used to create a local copy of Direct Damage which is then added to Current Stability.
	UPROPERTY(BlueprintReadOnly, Category = "Stability Attribute Set", meta = (HideFromLevelInfos))
	FGameplayAttributeData ReceivedDirectDamage;
	ATTRIBUTE_ACCESSORS(UALSXTStabilityAttributeSet, ReceivedDirectDamage)
	
	// Holds the current value for Stability.
	UPROPERTY(BlueprintReadOnly, Category = "Stability Attribute Set", ReplicatedUsing = OnRep_CurrentStability)
	FGameplayAttributeData CurrentStability;
	ATTRIBUTE_ACCESSORS(UALSXTStabilityAttributeSet, CurrentStability)

	// Holds the value for Maximum Stability.
	UPROPERTY(BlueprintReadOnly, Category = "Stability Attribute Set", ReplicatedUsing = OnRep_MaximumStability)
	FGameplayAttributeData MaximumStability;
	ATTRIBUTE_ACCESSORS(UALSXTStabilityAttributeSet, MaximumStability)

	// Holds the value for Stability Regeneration.
	UPROPERTY(BlueprintReadOnly, Category = "Stability Attribute Set", ReplicatedUsing = OnRep_StabilityRegeneration)
	FGameplayAttributeData StabilityRegeneration;
	ATTRIBUTE_ACCESSORS(UALSXTStabilityAttributeSet, StabilityRegeneration)

	// Holds the current bleeding amount
	UPROPERTY(BlueprintReadOnly, Category = "Stability Attribute Set", ReplicatedUsing = OnRep_Bleeding)
	FGameplayAttributeData Bleeding;
	ATTRIBUTE_ACCESSORS(UALSXTStabilityAttributeSet, Bleeding)

	// Holds the current bleed healing rate
	UPROPERTY(BlueprintReadOnly, Category = "Stability Attribute Set", ReplicatedUsing = OnRep_BleedHealing)
	FGameplayAttributeData BleedHealing;
	ATTRIBUTE_ACCESSORS(UALSXTStabilityAttributeSet, BleedHealing)

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayAttribute, FCustomAttributeMaxValue> AttributeMaxValue;
	
	UFUNCTION()
	virtual void OnRep_CurrentStability(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaximumStability(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_StabilityRegeneration(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Bleeding(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_BleedHealing(const FGameplayAttributeData& OldValue);
	
	
};
