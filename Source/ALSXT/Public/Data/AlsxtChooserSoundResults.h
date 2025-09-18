#pragma once

#include "NativeGameplayTags.h"
#include "AlsxtChooserSoundResults.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtBreathChooserSoundResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Sex", AllowPrivateAccess))
	FGameplayTag Sex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Voice Variant", AllowPrivateAccess))
	FGameplayTag VoiceVariant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Breath Type", AllowPrivateAccess))
	FGameplayTag BreathType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (AllowPrivateAccess))
	float Stamina {0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (AllowPrivateAccess))
	float Exhaustion {0.0f};

	bool operator==(const FAlsxtBreathChooserSoundResult& other) const
	{
		return (other.Sex == Sex) && (other.VoiceVariant == VoiceVariant) && (other.Stamina == Stamina) && (other.Exhaustion == Exhaustion);
	}
};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtHoldingBreathSoundResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Sex", AllowPrivateAccess))
	FGameplayTag Sex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Voice Variant", AllowPrivateAccess))
	FGameplayTag VoiceVariant;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Breath Type", AllowPrivateAccess))
	FGameplayTag BreathType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Holding Breath", AllowPrivateAccess))
	FGameplayTag HoldingBreathType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (AllowPrivateAccess))
	float Stamina {0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (AllowPrivateAccess))
	float Exhaustion {0.0f};


	bool operator==(const FAlsxtHoldingBreathSoundResult& other) const
	{
		return (other.Sex == Sex) && (other.VoiceVariant == VoiceVariant) && (other.BreathType == BreathType) && (other.HoldingBreathType == HoldingBreathType) && (other.Stamina == Stamina) && (other.Exhaustion == Exhaustion);
	}
};

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTCharacterMovementSoundResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.OverlayMode", AllowPrivateAccess))
	FGameplayTag Overlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Character Movement Sound", AllowPrivateAccess))
	FGameplayTag Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Object Weight", AllowPrivateAccess))
	float Weight {0.0f};

	bool operator==(const FALSXTCharacterMovementSoundResult& other) const
	{
		return (other.Overlay == Overlay) && (other.Type == Type) && (other.Weight == Weight);
	}
};

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTCharacterActionSoundResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Sex", AllowPrivateAccess))
	FGameplayTag Sex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Voice Variant", AllowPrivateAccess))
	FGameplayTag Variant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.OverlayMode", AllowPrivateAccess))
	FGameplayTag Overlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Action Strength", AllowPrivateAccess))
	FGameplayTag Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (AllowPrivateAccess))
	float Stamina {0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (AllowPrivateAccess))
	float Exhaustion {0.0f};

	bool operator==(const FALSXTCharacterActionSoundResult& other) const
	{
		return (other.Sex == Sex) && (other.Overlay == Overlay) && (other.Strength == Strength) && (other.Stamina == Stamina) && (other.Exhaustion == Exhaustion);
	}
};

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTCharacterDamageSoundResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Sex", AllowPrivateAccess))
	FGameplayTag Sex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Voice Variant", AllowPrivateAccess))
	FGameplayTag Variant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Impact Form", AllowPrivateAccess))
	FGameplayTag Form;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Attack Method", AllowPrivateAccess))
	FGameplayTag AttackMethod;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (AllowPrivateAccess))
	float Damage {0.0f} ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (AllowPrivateAccess))
	float CurrentHealth {0.0f};

	bool operator==(const FALSXTCharacterDamageSoundResult& other) const
	{
		return (other.Sex == Sex) && (other.Variant == Variant) && (other.Form == Form) && (other.AttackMethod == AttackMethod) && (other.Damage == Damage) && (other.CurrentHealth == CurrentHealth);
	}
};

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTWeaponActionSoundResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Weapon", AllowPrivateAccess))
	FGameplayTag Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser Sound Result", Meta = (Categories = "Als.Weapon Action", AllowPrivateAccess))
	FGameplayTag Type;


	bool operator==(const FALSXTWeaponActionSoundResult& other) const
	{
		return (other.Weapon == Weapon) && (other.Type == Type);
	}
};