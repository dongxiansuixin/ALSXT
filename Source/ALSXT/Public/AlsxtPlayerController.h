// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#pragma once

#include "CoreMinimal.h"
#include "AlsxtCharacterPlayer.h"
#include "ModularPlayerController.h"
#include "AlsxtPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class UAlsxtAbilitySystemComponent;

/**
* @file AlsxtPlayerController.h
* @brief template class that contains all shared Logic and Data for Player Classes.
* AAlsxtCharacterPlayer depends on AAlsxtPlayerState and AAlsxtPlayerController to function.
* Create a Blueprint class based on this class, do not use the C++ class directly in the Editor
*/

UCLASS()
class ALSXT_API AAlsxtPlayerController : public AModularPlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "References")
	TSoftObjectPtr<AAlsxtCharacterPlayer> AlsxtCharacterPlayer;
	
	UPROPERTY(VisibleAnywhere, Category = "References")
	TSoftObjectPtr<AAlsxtPlayerState> AlsxtPlayerState;

	UPROPERTY(EditAnywhere, Category = "References")
	TSoftObjectPtr<UAlsxtAbilitySystemComponent> AlsxtAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "ALSXT Player Controller")
	bool CanControlCharacter {true};

	UPROPERTY(VisibleAnywhere, Category = "ALSXT Player Controller")
	bool CanControlPawn {false};
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> LookMouseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> WalkAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> RagdollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> RollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> RotationModeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> ViewModeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> SwitchShoulderAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Input", Meta = (ClampMin = 0, ForceUnits = "x"))
	float LookUpMouseSensitivity{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Input", Meta = (ClampMin = 0, ForceUnits = "x"))
	float LookRightMouseSensitivity{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Input", Meta = (ClampMin = 0, ForceUnits = "deg/s"))
	float LookUpRate{90.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Input", Meta = (ClampMin = 0, ForceUnits = "deg/s"))
	float LookRightRate{240.0f};

public:
	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;
	
	virtual void Input_OnLookMouse(const FInputActionValue& ActionValue);

	virtual void Input_OnLook(const FInputActionValue& ActionValue);

	virtual void Input_OnMove(const FInputActionValue& ActionValue);

	virtual void Input_OnSprint(const FInputActionValue& ActionValue);

	virtual void Input_OnWalk();

	virtual void Input_OnCrouch();

	virtual void Input_OnJump(const FInputActionValue& ActionValue);

	virtual void Input_OnAim(const FInputActionValue& ActionValue);

	virtual void Input_OnRagdoll();

	virtual void Input_OnRoll();

	virtual void Input_OnRotationMode();

	virtual void Input_OnViewMode();

	virtual void Input_OnSwitchShoulder();
};
