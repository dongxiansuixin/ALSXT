// MIT

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AlsxtAttributeSetBase.h"
#include "AlsxtBreathAttributeSet.generated.h"


// Contains Attributes related to BreathRate. Any Character that uses BreathRate will need this Attribute Set.
//
//	Contents:
//	
//	CurrentBreathRate - Primarily used as a cost resource for Abilities.
//	MaximumBreathRate - The maximum amount of Breath the Character can have.
//	BreathRegeneration - How much Breath is gained per period of Regeneration.
UCLASS()
class ALSXT_API UAlsxtBreathAttributeSet : public UAlsxtAttributeSetBase
{
	GENERATED_BODY()

public:
	
	UAlsxtBreathAttributeSet();

	// Attribute Set Overrides.
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Set Attributes to replicate.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Holds the current value for Breath.
	UPROPERTY(BlueprintReadOnly, Category = "Breath Attribute Set", ReplicatedUsing = OnRep_CurrentBreathRate)
	FGameplayAttributeData CurrentBreathRate;
	ATTRIBUTE_ACCESSORS(UAlsxtBreathAttributeSet, CurrentBreathRate)

	// Holds the value for Maximum Breath.
	UPROPERTY(BlueprintReadOnly, Category = "Breath Attribute Set", ReplicatedUsing = OnRep_MaximumBreathRate)
	FGameplayAttributeData MaximumBreathRate;
	ATTRIBUTE_ACCESSORS(UAlsxtBreathAttributeSet, MaximumBreathRate)

	// Holds the current value for Breath Regeneration.
	UPROPERTY(BlueprintReadOnly, Category = "Breath Attribute Set", ReplicatedUsing = OnRep_BreathRegeneration)
	FGameplayAttributeData BreathRegeneration;
	ATTRIBUTE_ACCESSORS(UAlsxtBreathAttributeSet, BreathRegeneration)

protected:
	
	UFUNCTION()
	virtual void OnRep_CurrentBreathRate(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaximumBreathRate(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_BreathRegeneration(const FGameplayAttributeData& OldValue);
};