#include "AbilitySystem/Calculations/AlsxtGeecBreathingRate.h"
#include "AbilitySystem/AttributeSets/AlsxtStaminaAttributeSet.h" // Assuming this is the attribute set class.
#include "AbilitySystem/Calculations/AlsxtGeecBreathingRate.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"

// Define the attribute capture macro. This helps ensure proper attribute access.
#define DEFINE_ATTRIBUTE_CAPTUREDEF(Attribute, CaptureType) \
	Attribute##Def(UAlsxtStaminaAttributeSet::Get##Attribute##Attribute(), CaptureType)

UAlsxtGeecBreathingRate::UAlsxtGeecBreathingRate()
{
	// Define the attributes to capture from the target.
	// `Target` indicates the character receiving the Gameplay Effect.
	// `false` means we don't need a snapshot of the attribute at the start.
	StaminaDef = FGameplayEffectAttributeCaptureDefinition(UAlsxtStaminaAttributeSet::GetCurrentStaminaAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);
	MaxStaminaDef = FGameplayEffectAttributeCaptureDefinition(UAlsxtStaminaAttributeSet::GetMaximumStaminaAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);
	// UAlsxtGeecBreathingRate::FBreathingRateCaptureDefinition UAlsxtGeecBreathingRate::BreathingRateCaptureDefinition;

	// Add the capture definitions to the relevant attributes.
	RelevantAttributesToCapture.Add(StaminaDef);
	RelevantAttributesToCapture.Add(MaxStaminaDef);
	// RelevantAttributesToCapture.Add(BreathingRateCaptureDefinition.HoldingBreathLengthDef);
}

void UAlsxtGeecBreathingRate::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// --- Get information from the execution parameters ---
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluationParameters;

	// Get the ability system component of the character receiving the effect.
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!TargetAbilitySystemComponent)
	{
		return;
	}

	// --- Capture attribute values ---
	float Stamina = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(StaminaDef, EvaluationParameters, Stamina);

	float MaxStamina = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MaxStaminaDef, EvaluationParameters, MaxStamina);

	// --- Perform the calculation logic ---
	float BreathingRate = 0.0f;

	// This is a simple example. A more complex formula could be used.
	// For instance, the breathing rate could increase as stamina gets lower.
	if (MaxStamina > 0.0f)
	{
		float StaminaRatio = Stamina / MaxStamina;

		// Inverse relationship: lower stamina means higher breathing rate.
		// Use a clamped value to prevent extreme rates.
		BreathingRate = FMath::Lerp(5.0f, 1.0f, FMath::Clamp(StaminaRatio, 0.0f, 1.0f)); 
		
		// For example, if Stamina is 100% (Ratio 1.0), BreathingRate = 1.0 (calm).
		// If Stamina is 0% (Ratio 0.0), BreathingRate = 5.0 (heavy breathing).
	}
	else
	{
		// Default to a resting rate if max stamina is zero or invalid.
		BreathingRate = 1.0f; 
	}
	
	// --- Apply the output modifier ---
	// Create a new modifier for the 'BreathingRate' attribute.
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
		UAlsxtStaminaAttributeSet::GetBreathingRateAttribute(),
		EGameplayModOp::Override, // This will directly set the base value.
		BreathingRate
	));
}
