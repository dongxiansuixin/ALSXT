#pragma once

#include "NativeGameplayTags.h"
#include "Settings/AlsxtCharacterSoundSettings.h"
#include "Utility/AlsxtStructs.h"
#include "Settings/AlsxtCharacterBreathEffectsSettings.h"
#include "AlsxtCharacterSoundComponentInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UAlsxtCharacterSoundComponentInterface : public UInterface {
	GENERATED_BODY()
};

class ALSXT_API IAlsxtCharacterSoundComponentInterface {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character Sound Component Interface|Parameters")
	UAlsxtCharacterSoundSettings* SelectCharacterSoundSettings();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character Sound Component Interface|Parameters")
	UAlsxtWeaponSoundSettings* SelectWeaponSoundSettings();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Breath Effects")
	FAlsxtCharacterBreathEffectsSettings GetBreathEffectsSettings();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Parameters")
	FALSXTCharacterVoiceParameters GetVoiceParametersOld();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Breath Effects")
	float GetCurrentStamina() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Breath Effects")
	FGameplayTag GetCurrentStaminaTag() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Breath Effects")
	FGameplayTag GetCurrentBreathType() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Breath Effects")
	FString GetCurrentBreathSounds() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Breath Effects")
	FString GetCurrentBreathSound() const;

	// UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Breath Effects")
	// FString GetCurrentVocalizations() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Breath Effects")
	FString GetCurrentVocalization() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Breath Effects")
	bool CanPlayBreathSound();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Parameters")
	bool CanPlayActionSound();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Parameters")
	bool CanPlayCharacterMovementSound() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Parameters")
	bool CanPlayWeaponMovementSound() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Parameters")
	bool CanPlayDamageSound();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Parameters")
	bool ShouldPlayWeaponMovementSound(UPARAM(meta = (Categories = "Als.LocomotionAction"))const FGameplayTag& Type, UPARAM(meta = (Categories = "Als.Action Strength"))const FGameplayTag& Strength) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Parameters")
	bool ShouldPlayMovementAccentSound(UPARAM(meta = (Categories = "Als.LocomotionAction"))const FGameplayTag& Type, UPARAM(meta = (Categories = "Als.Object Weight"))const FGameplayTag& Weight) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Parameters")
	bool ShouldPlayDamageSound();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Parameters")
	FVector GetVoiceSocketLocation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Parameters")
	FRotator GetVoiceSocketRotation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Parameters")
	FGameplayTag GetHoldingBreath();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Movement", Meta = (AutoCreateRefTerm = "Type, Weight"))
	void PlayCharacterMovementSound(bool AccentSound, bool WeaponSound, UPARAM(meta = (Categories = "Als.Character Movement Sound"))const FGameplayTag& Type, UPARAM(meta = (Categories = "Als.Object Weight"))const FGameplayTag& Weight);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Sound Component Interface|Breath Effects|Events", Meta = (AutoCreateRefTerm = "StaminaOverride"))
	void PlayBreathEffects(UPARAM(meta = (Categories = "Als.Stamina"))const FGameplayTag& StaminaOverride);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Events", Meta = (AutoCreateRefTerm = "Type, SoundSex, Variant, Overlay, Strength"))
	void PlayActionSound(bool MovementSound, bool AccentSound, bool WeaponSound, UPARAM(meta = (Categories = "Als.Character Movement Sound"))const FGameplayTag& Type, UPARAM(meta = (Categories = "Als.Sex"))const FGameplayTag& SoundSex, UPARAM(meta = (Categories = "Als.Voice Variant"))const FGameplayTag& Variant, UPARAM(meta = (Categories = "Als.OverlayMode"))const FGameplayTag& Overlay, UPARAM(meta = (Categories = "Als.Action Strength"))const FGameplayTag& Strength, const float Stamina);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Events", Meta = (AutoCreateRefTerm = "SoundSex, Variant, Overlay, Strength, AttackMode"))
	void PlayAttackSound(bool MovementSound, bool AccentSound, bool WeaponSound, UPARAM(meta = (Categories = "Als.Sex"))const FGameplayTag& SoundSex, UPARAM(meta = (Categories = "Als.Voice Variant"))const FGameplayTag& Variant, UPARAM(meta = (Categories = "Als.OverlayMode"))const FGameplayTag& Overlay, UPARAM(meta = (Categories = "Als.Action Strength"))const FGameplayTag& Strength, const FGameplayTag& AttackMode, const float Stamina);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Events", Meta = (AutoCreateRefTerm = "SoundSex, Variant, Overlay, AttackMethod, Strength, AttackForm"))
	void PlayDamageSound(bool MovementSound, bool AccentSound, bool WeaponSound, UPARAM(meta = (Categories = "Als.Sex"))const FGameplayTag& SoundSex, UPARAM(meta = (Categories = "Als.Voice Variant"))const FGameplayTag& Variant, UPARAM(meta = (Categories = "Als.OverlayMode"))const FGameplayTag& Overlay, UPARAM(meta = (Categories = "Als.Attack Method"))const FGameplayTag& AttackMethod, UPARAM(meta = (Categories = "Als.Action Strength"))const FGameplayTag& Strength, const FGameplayTag& AttackForm, const float Damage);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Breath Effects Interface|Events", Meta = (AutoCreateRefTerm = "SoundSex, Variant, Overlay, Strength, AttackForm"))
	void PlayDeathSound(UPARAM(meta = (Categories = "Als.Sex"))const FGameplayTag& SoundSex, UPARAM(meta = (Categories = "Als.Voice Variant"))const FGameplayTag& Variant, UPARAM(meta = (Categories = "Als.OverlayMode"))const FGameplayTag& Overlay, UPARAM(meta = (Categories = "Als.Attack Method"))const FGameplayTag& AttackMethod, UPARAM(meta = (Categories = "Als.Action Strength"))const FGameplayTag& Strength, const FGameplayTag& AttackForm, const float Damage);
};