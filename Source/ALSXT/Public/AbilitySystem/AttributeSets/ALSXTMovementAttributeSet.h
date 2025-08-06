// MIT

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ALSXTAttributeSetBase.h"
#include "ALSXTMovementAttributeSet.generated.h"


// Contains Attributes related to Movement.
//
//	Contents:
UCLASS()
class ALSXT_API UALSXTMovementAttributeSet : public UALSXTAttributeSetBase
{
	GENERATED_BODY()

public:
	
	UALSXTMovementAttributeSet();

	// Attribute Set Overrides.
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Set Attributes to replicate.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Movement Attribute Set", ReplicatedUsing = OnRep_MovementSpeedMultiplier)
	FGameplayAttributeData MovementSpeedMultiplier;
	ATTRIBUTE_ACCESSORS(UALSXTMovementAttributeSet, MovementSpeedMultiplier)

	UPROPERTY(BlueprintReadOnly, Category = "Movement Attribute Set", ReplicatedUsing = OnRep_MovementAccelerationMultiplier)
	FGameplayAttributeData MovementAccelerationMultiplier;
	ATTRIBUTE_ACCESSORS(UALSXTMovementAttributeSet, MovementAccelerationMultiplier)
protected:
	
	UFUNCTION()
	virtual void OnRep_MovementSpeedMultiplier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MovementAccelerationMultiplier(const FGameplayAttributeData& OldValue);
};