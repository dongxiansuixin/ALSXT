// MIT

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ALSXTAttributeSetBase.h"
#include "ALSXTStaminaAttributeSet.generated.h"


// Contains Attributes related to Stamina. Any Character that uses Stamina will need this Attribute Set.
//
//	Contents:
//	
//	CurrentStamina - Primarily used as a cost resource for Abilities.
//	MaximumStamina - The maximum amount of Stamina the Character can have.
//	StaminaRegeneration - How much Stamina is gained per period of Regeneration.
UCLASS()
class ALSXT_API UALSXTStaminaAttributeSet : public UALSXTAttributeSetBase
{
	GENERATED_BODY()

public:
	
	UALSXTStaminaAttributeSet();

	// Attribute Set Overrides.
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Set Attributes to replicate.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Holds the current value for Stamina.
	UPROPERTY(BlueprintReadOnly, Category = "Stamina Attribute Set", ReplicatedUsing = OnRep_CurrentStamina)
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UALSXTStaminaAttributeSet, CurrentStamina)

	// Holds the value for Maximum Stamina.
	UPROPERTY(BlueprintReadOnly, Category = "Stamina Attribute Set", ReplicatedUsing = OnRep_MaximumStamina)
	FGameplayAttributeData MaximumStamina;
	ATTRIBUTE_ACCESSORS(UALSXTStaminaAttributeSet, MaximumStamina)

	// Holds the current value for Stamina Regeneration.
	UPROPERTY(BlueprintReadOnly, Category = "Stamina Attribute Set", ReplicatedUsing = OnRep_StaminaRegeneration)
	FGameplayAttributeData StaminaRegeneration;
	ATTRIBUTE_ACCESSORS(UALSXTStaminaAttributeSet, StaminaRegeneration)

protected:
	
	UFUNCTION()
	virtual void OnRep_CurrentStamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaximumStamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_StaminaRegeneration(const FGameplayAttributeData& OldValue);
};