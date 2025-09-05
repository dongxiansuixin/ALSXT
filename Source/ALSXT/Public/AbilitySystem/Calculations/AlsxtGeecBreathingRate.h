#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AbilitySystem/AttributeSets/AlsxtStaminaAttributeSet.h"
#include "AbilitySystem/AttributeSets/AlsxtBreathAttributeSet.h"
#include "AlsxtGeecBreathingRate.generated.h"

/**
 * Custom execution calculation for breathing rate.
 */
UCLASS()
class ALSXT_API UAlsxtGeecBreathingRate : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	// Constructor where attribute captures are defined.
	UAlsxtGeecBreathingRate();

protected:
	// This is the core function where you perform the calculation.
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

private:
	// Capture definition for the Stamina attribute.
	FGameplayEffectAttributeCaptureDefinition StaminaDef;

	// Capture definition for the MaxStamina attribute.
	FGameplayEffectAttributeCaptureDefinition MaxStaminaDef;
};