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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetupInputComponentDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnyInputDetected);

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

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	FInputActionValue InputMantleValue;

	UPROPERTY(BlueprintAssignable)
	FSetupInputComponentDelegate OnSetupPlayerInputComponentUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAnyInputDetected OnAnyInputDetected;


private:
	UPROPERTY(VisibleAnywhere, Category = "References")
	TSoftObjectPtr<AAlsxtCharacterPlayer> AlsxtCharacterPlayer;
	
	UPROPERTY(VisibleAnywhere, Category = "References")
	TSoftObjectPtr<AAlsxtPlayerState> AlsxtPlayerState;
	

	UPROPERTY(EditAnywhere, Category = "References")
	TSoftObjectPtr<UAlsxtAbilitySystemComponent> AlsxtAbilitySystemComponent;

	void HandleAnyInputKey();
	
	UPROPERTY(VisibleAnywhere, Category = "ALSXT Player Controller")
	bool CanControlCharacter {true};

	UPROPERTY(VisibleAnywhere, Category = "ALSXT Player Controller")
	bool CanControlPawn {false};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Replicated, Meta = (AllowPrivateAccess))
	FVector MovementInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Replicated, Meta = (AllowPrivateAccess))
	FVector2D PreviousLookInput;
	
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

	////
	///
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> AnyInputDetectionAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> MantleAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> AimToggleAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> FocusAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> FreelookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> ToggleFreelookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> PrimaryInteractionAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> SecondaryInteractionAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> ToggleGaitAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> ToggleCombatReadyAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> BlockAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> LeanLeftAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> ToggleLeanLeftAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> LeanRightAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> ToggleLeanRightAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> SlideAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> SwitchWeaponReadyPositionAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> SwitcWeaponFirearmStanceAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> SwitchGripPositionAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> SwitchForegripPositionAction;
	///
	///

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Input", Meta = (ClampMin = 0, ForceUnits = "x"))
	float LookUpMouseSensitivity{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Input", Meta = (ClampMin = 0, ForceUnits = "x"))
	float LookRightMouseSensitivity{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Input", Meta = (ClampMin = 0, ForceUnits = "deg/s"))
	float LookUpRate{90.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Input", Meta = (ClampMin = 0, ForceUnits = "deg/s"))
	float LookRightRate{240.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character Example", Meta = (AllowPrivateAccess))
	float PreviousYaw{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character Example", Meta = (AllowPrivateAccess))
	float PreviousPitch{ 0.0f };

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

	//

	
	virtual void Input_OnMantle(const FInputActionValue& ActionValue);
	
	virtual void Input_OnToggleAim();
	
	virtual void Input_OnFocus(const FInputActionValue& ActionValue);
	
	virtual void Input_OnFreelook(const FInputActionValue& ActionValue);

	virtual void Input_OnToggleFreelook(const FInputActionValue& ActionValue);
	
	virtual void Input_OnToggleGait();
	
	virtual void Input_OnToggleCombatReady();
	
	virtual void Input_OnLeanLeft(const FInputActionValue& ActionValue);

	virtual void Input_OnToggleLeanLeft(const FInputActionValue& ActionValue);
	
	virtual void Input_OnLeanRight(const FInputActionValue& ActionValue);

	virtual void Input_OnToggleLeanRight(const FInputActionValue& ActionValue);
	
	virtual void Input_OnSwitchWeaponFirearmStance();
	
	virtual void Input_OnSwitchWeaponReadyPosition();
	
	virtual void Input_OnSwitchGripPosition();
	
	virtual void Input_OnSwitchForegripPosition();
	
	virtual void Input_OnBlock(const FInputActionValue& ActionValue);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Als|Input Actions")
	void Input_OnPrimaryInteraction();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Als|Input Actions")
	void Input_OnSecondaryInteraction();
};
