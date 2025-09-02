// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#include "AlsxtPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/Data/AlsxtGasGameplayTags.h"
#include "AbilitySystem/Interfaces/AlsxtAbilitySystemInterface.h"
#include "Utility/AlsGameplayTags.h"
#include "Utility/AlsVector.h"

// #include UE_INLINE_GENERATED_CPP_BY_NAME(AlsxtPlayerController)

/**
* @file AlsxtPlayerController.cpp
* @brief template class that contains all shared Logic and Data for Player Classes.
* AAlsxtCharacterPlayer depends on AAlsxtPlayerState and AAlsxtPlayerController to function.
* Create a Blueprint class based on this class, do not use the C++ class directly in the Editor
*/

void AAlsxtPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Retrieve and Set a Reference to AAlsxtPlayerState
	if (const TSoftObjectPtr<AAlsxtPlayerState> CurrentAlsxtPlayerState = Cast<AAlsxtPlayerState>(PlayerState.Get()))
	{
		AlsxtPlayerState = CurrentAlsxtPlayerState;
	}

	// Retrieve and Set a Reference to AAlsxtCharacterPlayer
	if (const TSoftObjectPtr<AAlsxtCharacterPlayer> CurrentAlsxtPlayerCharacter = Cast<AAlsxtCharacterPlayer>(GetPawn()))
	{
		AlsxtCharacterPlayer = CurrentAlsxtPlayerCharacter;
	}

	// Retrieve and Set a Reference to AlsxtAbilitySystemComponent
	if (const IAlsxtAbilitySystemInterface* AlsxtAbilitySystemInterface = Cast<IAlsxtAbilitySystemInterface>(PlayerState.Get()))
	{
		AlsxtAbilitySystemComponent = AlsxtAbilitySystemInterface->GetAlsxtAbilitySystemComponent();
	}

	// Get the Enhanced Input Local Player Subsystem and add the mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0); // Priority 0
		}
	}
}

void AAlsxtPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Cast the InputComponent to UEnhancedInputComponent
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind Input Actions
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &ThisClass::Input_OnMove);
		}
		EnhancedInputComponent->BindAction(LookMouseAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLookMouse);
		EnhancedInputComponent->BindAction(LookMouseAction, ETriggerEvent::Canceled, this, &ThisClass::Input_OnLookMouse);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLook);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Canceled, this, &ThisClass::Input_OnLook);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnMove);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &ThisClass::Input_OnMove);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this, &ThisClass::Input_OnSprint);
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnWalk);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnCrouch);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, this, &ThisClass::Input_OnJump);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnAim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Canceled, this, &ThisClass::Input_OnAim);
		EnhancedInputComponent->BindAction(RagdollAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRagdoll);
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRoll);
		EnhancedInputComponent->BindAction(RotationModeAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRotationMode);
		EnhancedInputComponent->BindAction(ViewModeAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnViewMode);
		EnhancedInputComponent->BindAction(SwitchShoulderAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSwitchShoulder);
	}
}

void AAlsxtPlayerController::Input_OnLookMouse(const FInputActionValue& ActionValue)
{
	const FVector2f Value{ActionValue.Get<FVector2D>()};

	AddPitchInput(Value.Y * LookUpMouseSensitivity);
	AddYawInput(Value.X * LookRightMouseSensitivity);
}

void AAlsxtPlayerController::Input_OnLook(const FInputActionValue& ActionValue)
{
	const FVector2f Value{ActionValue.Get<FVector2D>()};

	AddPitchInput(Value.Y * LookUpRate);
	AddYawInput(Value.X * LookRightRate);
}

void AAlsxtPlayerController::Input_OnMove(const FInputActionValue& ActionValue)
{
	const auto Value{UAlsVector::ClampMagnitude012D(ActionValue.Get<FVector2D>())};

	auto ViewRotation{AlsxtCharacterPlayer.Get()->GetViewState().Rotation};
	
	// Use exact camera rotation instead of target rotation whenever possible.

	FVector ViewLocation;
	GetPlayerViewPoint(ViewLocation, ViewRotation);

	const auto ForwardDirection{UAlsVector::AngleToDirectionXY(UE_REAL_TO_FLOAT(ViewRotation.Yaw))};
	const auto RightDirection{UAlsVector::PerpendicularCounterClockwiseXY(ForwardDirection)};

	AlsxtCharacterPlayer.Get()->AddMovementInput(ForwardDirection * Value.Y + RightDirection * Value.X);
}

void AAlsxtPlayerController::Input_OnSprint(const FInputActionValue& ActionValue)
{
	AlsxtCharacterPlayer.Get()->SetDesiredGait(ActionValue.Get<bool>() ? AlsGaitTags::Sprinting : AlsGaitTags::Running);
}

void AAlsxtPlayerController::Input_OnWalk()
{
	if (AlsxtCharacterPlayer.Get()->GetDesiredGait() == AlsGaitTags::Walking)
	{
		AlsxtCharacterPlayer.Get()->SetDesiredGait(AlsGaitTags::Running);
	}
	else if (AlsxtCharacterPlayer.Get()->GetDesiredGait() == AlsGaitTags::Running)
	{
		AlsxtCharacterPlayer.Get()->SetDesiredGait(AlsGaitTags::Walking);
	}
}

void AAlsxtPlayerController::Input_OnCrouch()
{
	if (AlsxtCharacterPlayer.Get()->GetDesiredStance() == AlsStanceTags::Standing)
	{
		AlsxtCharacterPlayer.Get()->SetDesiredStance(AlsStanceTags::Crouching);
	}
	else if (AlsxtCharacterPlayer.Get()->GetDesiredStance() == AlsStanceTags::Crouching)
	{
		AlsxtCharacterPlayer.Get()->SetDesiredStance(AlsStanceTags::Standing);
	}
}

void AAlsxtPlayerController::Input_OnJump(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		if (AlsxtCharacterPlayer.Get()->StopRagdolling())
		{
			return;
		}

		if (AlsxtCharacterPlayer.Get()->StartMantlingGrounded())
		{
			return;
		}

		if (AlsxtCharacterPlayer.Get()->GetStance() == AlsStanceTags::Crouching)
		{
			AlsxtCharacterPlayer.Get()->SetDesiredStance(AlsStanceTags::Standing);
			return;
		}
		const FGameplayTagContainer TagsContainer {ALSXTAbilityGameplayTags::Jump};
		AlsxtAbilitySystemComponent->TryActivateAbilitiesByTag(TagsContainer);
		AlsxtCharacterPlayer.Get()->Jump();
	}
	else
	{
		AlsxtCharacterPlayer.Get()->StopJumping();
	}
}

void AAlsxtPlayerController::Input_OnAim(const FInputActionValue& ActionValue)
{
	AlsxtCharacterPlayer.Get()->SetDesiredAiming(ActionValue.Get<bool>());
}

void AAlsxtPlayerController::Input_OnRagdoll()
{
	if (!AlsxtCharacterPlayer.Get()->StopRagdolling())
	{
		AlsxtCharacterPlayer.Get()->StartRagdolling();
	}
}

void AAlsxtPlayerController::Input_OnRoll()
{
	static constexpr auto PlayRate{1.3f};

	AlsxtCharacterPlayer.Get()->StartRolling(PlayRate);
}

void AAlsxtPlayerController::Input_OnRotationMode()
{
	AlsxtCharacterPlayer.Get()->SetDesiredRotationMode(AlsxtCharacterPlayer.Get()->GetDesiredRotationMode() == AlsRotationModeTags::VelocityDirection
		                       ? AlsRotationModeTags::ViewDirection
		                       : AlsRotationModeTags::VelocityDirection);
}

void AAlsxtPlayerController::Input_OnViewMode()
{
	AlsxtCharacterPlayer.Get()->SetViewMode(AlsxtCharacterPlayer.Get()->GetViewMode() == AlsViewModeTags::ThirdPerson ? AlsViewModeTags::FirstPerson : AlsViewModeTags::ThirdPerson);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AAlsxtPlayerController::Input_OnSwitchShoulder()
{
	AlsxtCharacterPlayer.Get()->Camera->SetRightShoulder(!AlsxtCharacterPlayer.Get()->Camera->IsRightShoulder());
}