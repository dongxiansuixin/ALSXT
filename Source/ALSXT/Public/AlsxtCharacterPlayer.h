// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#pragma once

#include "CoreMinimal.h"
#include "AlsxtCharacter.h"
#include "AbilitySystem/PlayerState/AlsxtPlayerState.h"
#include "AlsxtCharacterPlayer.generated.h"

/**
* @file AlsxtCharacterPlayer.h
* @brief template class that contains all shared Logic and Data for Player Classes.
* AAlsxtCharacterPlayer depends on AAlsxtPlayerState and AAlsxtPlayerController to function.
* Create a Blueprint class based on this class, do not use the C++ class directly in the Editor
*/

UCLASS()
class ALSXT_API AAlsxtCharacterPlayer : public AAlsxtCharacter
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(UInputComponent* Input) override;

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;
	
	TSoftObjectPtr<APlayerState> PlayerState;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Als|Input Actions")
	void Input_OnPrimaryInteraction();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Als|Input Actions")
	void Input_OnSecondaryInteraction();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputMappingContext> InputMappingContextNew;

	TObjectPtr<UEnhancedInputComponent> EnhancedInput;

	virtual void OnRep_PlayerState() override;
	
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
    
    virtual void Input_OnMantle(const FInputActionValue& ActionValue);

    virtual void Input_OnToggleAim();
   
    virtual void Input_OnFocus(const FInputActionValue& ActionValue);
   
    virtual void Input_OnFreelook(const FInputActionValue& ActionValue);
   
    virtual void Input_OnToggleGait();
   
    virtual void Input_OnToggleCombatReady();

	virtual void Input_OnBlock(const FInputActionValue& ActionValue);
   
    virtual void Input_OnLeanLeft(const FInputActionValue& ActionValue);
   
    virtual void Input_OnLeanRight(const FInputActionValue& ActionValue);
    
    virtual void Input_OnSwitchWeaponFirearmStance();
   
    virtual void Input_OnSwitchWeaponReadyPosition();
    
    virtual void Input_OnSwitchGripPosition();
    
    virtual void Input_OnSwitchForegripPosition();
};
