// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#include "AlsxtPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/Data/AlsxtGasGameplayTags.h"
#include "AbilitySystem/Interfaces/AlsxtAbilitySystemInterface.h"
#include "Utility/AlsGameplayTags.h"
#include "Utility/AlsVector.h"
#include "Net/UnrealNetwork.h"

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

void AAlsxtPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Parameters;
	Parameters.bIsPushBased = true;
	Parameters.Condition = COND_SkipOwner;
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, PreviousLookInput, Parameters)
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, MovementInput, Parameters)
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
		if (AnyInputDetectionAction)
		{
			EnhancedInputComponent->BindAction(AnyInputDetectionAction, ETriggerEvent::Triggered, this, &ThisClass::HandleAnyInputKey);
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
		
		EnhancedInputComponent->BindAction(AimToggleAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnToggleAim);
		EnhancedInputComponent->BindAction(FocusAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnFocus);
		
		EnhancedInputComponent->BindAction(FreelookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnFreelook);
		EnhancedInputComponent->BindAction(ToggleFreelookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnToggleFreelook);
		EnhancedInputComponent->BindAction(ToggleGaitAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnToggleGait);
		EnhancedInputComponent->BindAction(ToggleCombatReadyAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnToggleCombatReady);
		EnhancedInputComponent->BindAction(PrimaryInteractionAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnPrimaryInteraction);
		EnhancedInputComponent->BindAction(SecondaryInteractionAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSecondaryInteraction);
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnBlock);

		
		EnhancedInputComponent->BindAction(SwitchWeaponReadyPositionAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSwitchWeaponReadyPosition);
		EnhancedInputComponent->BindAction(SwitchGripPositionAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSwitchGripPosition);
		EnhancedInputComponent->BindAction(SwitchForegripPositionAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSwitchForegripPosition);


		EnhancedInputComponent->BindAction(LeanLeftAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLeanLeft);
		EnhancedInputComponent->BindAction(ToggleLeanLeftAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnToggleLeanLeft);
		EnhancedInputComponent->BindAction(LeanRightAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLeanRight);
		EnhancedInputComponent->BindAction(ToggleLeanRightAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnToggleLeanRight);


		EnhancedInputComponent->BindAction(MantleAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnMantle);
		InputMantleValue = EnhancedInputComponent->GetBoundActionValue(MantleAction);
		OnSetupPlayerInputComponentUpdated.Broadcast();
	}
}

void AAlsxtPlayerController::HandleAnyInputKey()
{
	OnAnyInputDetected.Broadcast();
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

void AAlsxtPlayerController::Input_OnMantle(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		// RefreshMantle();
	}
	else
	{

	}
}

void AAlsxtPlayerController::Input_OnToggleAim()
{
	if (IAlsxtHeldItemInterface::Execute_IsHoldingAimableItem(this)) 
	{
		if (AlsxtCharacterPlayer->GetDesiredRotationMode() == AlsRotationModeTags::Aiming)
		{
			AlsxtCharacterPlayer->SetDesiredRotationMode(AlsRotationModeTags::ViewDirection);
			AlsxtCharacterPlayer->SetDesiredCombatStance(ALSXTCombatStanceTags::Ready);
		}
		if (AlsxtCharacterPlayer->CanAim())
		{
			AlsxtCharacterPlayer->SetViewMode(AlsViewModeTags::FirstPerson);
			AlsxtCharacterPlayer->SetDesiredCombatStance(ALSXTCombatStanceTags::Aiming);
			AlsxtCharacterPlayer->SetDesiredRotationMode(AlsRotationModeTags::Aiming);
		}
	}
}

void AAlsxtPlayerController::Input_OnFocus(const FInputActionValue& ActionValue)
{
	if (AlsxtCharacterPlayer->CanFocus())
	{
		if (ActionValue.Get<bool>())
		{
			AlsxtCharacterPlayer->SetDesiredFocus(ALSXTFocusedTags::True);
		}
		else
		{
			AlsxtCharacterPlayer->SetDesiredFocus(ALSXTFocusedTags::False);
		}
	}
}

void AAlsxtPlayerController::Input_OnFreelook(const FInputActionValue& ActionValue)
{
	if (AlsxtCharacterPlayer->CanFreelook())
	{
		if (ActionValue.Get<bool>())
		{
			// AlsxtCharacterPlayer->ActivateFreelooking();
		}
		else
		{
			// AlsxtCharacterPlayer->DeactivateFreelooking();
		}
	}
}

void AAlsxtPlayerController::Input_OnToggleFreelook(const FInputActionValue& ActionValue)
{
	if (AlsxtCharacterPlayer->CanFreelook())
	{
		if (ActionValue.Get<bool>())
		{
			// AlsxtCharacterPlayer->ActivateFreelooking();
		}
		else
		{
			// AlsxtCharacterPlayer->DeactivateFreelooking();
		}
	}
}

void AAlsxtPlayerController::Input_OnBlock(const FInputActionValue& ActionValue)
{
	FAlsxtDefensiveModeState PreviousDefensiveModeState = AlsxtCharacterPlayer->GetDefensiveModeState();

	if (AlsxtCharacterPlayer->CanEnterBlockingDefensiveMode())
	{
		if (ActionValue.Get<bool>() == true)
		{
			FAlsxtDefensiveModeState NewDefensiveModeState = AlsxtCharacterPlayer->GetDefensiveModeState();
			NewDefensiveModeState.Mode = ALSXTDefensiveModeTags::Anticipation;
			NewDefensiveModeState.AnticipationMode = ALSXTDefensiveModeTags::Anticipation;
			NewDefensiveModeState.AnticipationSide = PreviousDefensiveModeState.AnticipationSide == FGameplayTag::EmptyTag ? ALSXTImpactSideTags::Front : PreviousDefensiveModeState.AnticipationSide;
			NewDefensiveModeState.AnticipationHeight = PreviousDefensiveModeState.AnticipationHeight == FGameplayTag::EmptyTag ? ALSXTImpactHeightTags::Middle : PreviousDefensiveModeState.AnticipationHeight;
			NewDefensiveModeState.ObstacleMode = FGameplayTag::EmptyTag;
			NewDefensiveModeState.ObstacleSide = FGameplayTag::EmptyTag;
			NewDefensiveModeState.ObstacleHeight = FGameplayTag::EmptyTag;
			AlsxtCharacterPlayer->SetDefensiveModeState(NewDefensiveModeState);
			// SetDesiredDefensiveMode(ALSXTDefensiveModeTags::Blocking);

		}
		else 
		{
			// ResetDefensiveModeState();
			FAlsxtDefensiveModeState NewDefensiveModeState = AlsxtCharacterPlayer->GetDefensiveModeState();
			NewDefensiveModeState.Mode = PreviousDefensiveModeState.Mode == ALSXTDefensiveModeTags::Anticipation ? FGameplayTag::EmptyTag : PreviousDefensiveModeState.Mode;
			NewDefensiveModeState.AnticipationMode = FGameplayTag::EmptyTag;
			NewDefensiveModeState.AnticipationSide = FGameplayTag::EmptyTag;
			NewDefensiveModeState.AnticipationHeight = FGameplayTag::EmptyTag;
			NewDefensiveModeState.ObstacleMode = FGameplayTag::EmptyTag;
			NewDefensiveModeState.ObstacleSide = FGameplayTag::EmptyTag;
			NewDefensiveModeState.ObstacleHeight = FGameplayTag::EmptyTag;
			AlsxtCharacterPlayer->SetDefensiveModeState(NewDefensiveModeState);
			// SetDesiredDefensiveMode(FGameplayTag::EmptyTag);
		}
	}
	else if ((AlsxtCharacterPlayer->GetDesiredDefensiveMode() == ALSXTDefensiveModeTags::Blocking) && (ActionValue.Get<bool>()  == false))
	{
		FAlsxtDefensiveModeState NewDefensiveModeState = AlsxtCharacterPlayer->GetDefensiveModeState();
		NewDefensiveModeState.Mode = PreviousDefensiveModeState.Mode == ALSXTDefensiveModeTags::Anticipation ? FGameplayTag::EmptyTag : PreviousDefensiveModeState.Mode;
		NewDefensiveModeState.AnticipationMode = FGameplayTag::EmptyTag;
		NewDefensiveModeState.AnticipationSide = FGameplayTag::EmptyTag;
		NewDefensiveModeState.AnticipationHeight = FGameplayTag::EmptyTag;
		NewDefensiveModeState.ObstacleMode = FGameplayTag::EmptyTag;
		NewDefensiveModeState.ObstacleSide = FGameplayTag::EmptyTag;
		NewDefensiveModeState.ObstacleHeight = FGameplayTag::EmptyTag;
		AlsxtCharacterPlayer->SetDefensiveModeState(NewDefensiveModeState);
		AlsxtCharacterPlayer->SetDesiredDefensiveMode(FGameplayTag::EmptyTag);
	}
}


void AAlsxtPlayerController::Input_OnLeanLeft(const FInputActionValue & ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		if (AlsxtCharacterPlayer->CanLean())
		{
			AlsxtCharacterPlayer->SetDesiredLean(ALSXTLeanDirectionTags::Left);
			FAlsxtPoseState NewPoseState = AlsxtCharacterPlayer->GetALSXTPoseState();
			NewPoseState.LeanDirection = ALSXTLeanDirectionTags::Left;
			AlsxtCharacterPlayer->SetALSXTPoseState(NewPoseState);
		}
	}
	else
	{
		AlsxtCharacterPlayer->SetDesiredLean(FGameplayTag::EmptyTag);
		FAlsxtPoseState NewPoseState = AlsxtCharacterPlayer->GetALSXTPoseState();
		NewPoseState.LeanDirection = FGameplayTag::EmptyTag;
		AlsxtCharacterPlayer->SetALSXTPoseState(NewPoseState);
	}
}

void AAlsxtPlayerController::Input_OnLeanRight(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		if (AlsxtCharacterPlayer->CanLean())
		{
			AlsxtCharacterPlayer->SetDesiredLean(ALSXTLeanDirectionTags::Right);
			FAlsxtPoseState NewPoseState = AlsxtCharacterPlayer->GetALSXTPoseState();
			NewPoseState.LeanDirection = ALSXTLeanDirectionTags::Right;
			AlsxtCharacterPlayer->SetALSXTPoseState(NewPoseState);
		}
	}
	else
	{
		AlsxtCharacterPlayer->SetDesiredLean(FGameplayTag::EmptyTag);
		FAlsxtPoseState NewPoseState = AlsxtCharacterPlayer->GetALSXTPoseState();
		NewPoseState.LeanDirection = FGameplayTag::EmptyTag;
		AlsxtCharacterPlayer->SetALSXTPoseState(NewPoseState);
	}
}

void AAlsxtPlayerController::Input_OnToggleLeanLeft(const FInputActionValue & ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		if (AlsxtCharacterPlayer->CanLean())
		{
			AlsxtCharacterPlayer->SetDesiredLean(ALSXTLeanDirectionTags::Left);
			FAlsxtPoseState NewPoseState = AlsxtCharacterPlayer->GetALSXTPoseState();
			NewPoseState.LeanDirection = ALSXTLeanDirectionTags::Left;
			AlsxtCharacterPlayer->SetALSXTPoseState(NewPoseState);
		}
	}
	else
	{
		AlsxtCharacterPlayer->SetDesiredLean(FGameplayTag::EmptyTag);
		FAlsxtPoseState NewPoseState = AlsxtCharacterPlayer->GetALSXTPoseState();
		NewPoseState.LeanDirection = FGameplayTag::EmptyTag;
		AlsxtCharacterPlayer->SetALSXTPoseState(NewPoseState);
	}
}

void AAlsxtPlayerController::Input_OnToggleLeanRight(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		if (AlsxtCharacterPlayer->CanLean())
		{
			AlsxtCharacterPlayer->SetDesiredLean(ALSXTLeanDirectionTags::Right);
			FAlsxtPoseState NewPoseState = AlsxtCharacterPlayer->GetALSXTPoseState();
			NewPoseState.LeanDirection = ALSXTLeanDirectionTags::Right;
			AlsxtCharacterPlayer->SetALSXTPoseState(NewPoseState);
		}
	}
	else
	{
		AlsxtCharacterPlayer->SetDesiredLean(FGameplayTag::EmptyTag);
		FAlsxtPoseState NewPoseState = AlsxtCharacterPlayer->GetALSXTPoseState();
		NewPoseState.LeanDirection = FGameplayTag::EmptyTag;
		AlsxtCharacterPlayer->SetALSXTPoseState(NewPoseState);
	}
}

void AAlsxtPlayerController::Input_OnSwitchWeaponFirearmStance()
{
	if (AlsxtCharacterPlayer->GetDesiredCombatStance() == ALSXTCombatStanceTags::Neutral)
	{
		return;
	}
	else
	{
		FGameplayTagContainer AvailableStances = AlsxtCharacterPlayer->GetAvailableFirearmStances();
		TArray<FGameplayTag> AvailableStancesArray;
		AvailableStances.GetGameplayTagArray(AvailableStancesArray);
		if (AvailableStances.Num() <= 0 || AvailableStances.Num() == 1 && AvailableStancesArray[0] == AlsxtCharacterPlayer->GetDesiredWeaponFirearmStance())
		{
			return;
		}
		int CurrentIndex = AvailableStancesArray.IndexOfByKey(AlsxtCharacterPlayer->GetDesiredWeaponFirearmStance());
		int NextIndex;
		if ((CurrentIndex + 1) > (AvailableStancesArray.Num() - 1))
		{
			NextIndex = 0;
		}
		else
		{
			NextIndex = CurrentIndex + 1;
		}
		AlsxtCharacterPlayer->SetDesiredWeaponFirearmStance(AvailableStancesArray[NextIndex]);
	}
}

void AAlsxtPlayerController::Input_OnSwitchWeaponReadyPosition()
{
	TArray<FGameplayTag> AvailablePositions;
	// TArray<FGameplayTag> AvailablePositions = (GetDesiredCombatStance() == ALSXTCombatStanceTags::Neutral) ? {ALSXTWeaponReadyPositionTags::PatrolReady, ALSXTWeaponReadyPositionTags::HighReady, ALSXTWeaponReadyPositionTags::LowReady, ALSXTWeaponReadyPositionTags::Hidden } : { ALSXTWeaponReadyPositionTags::Ready, ALSXTWeaponReadyPositionTags::Retention, ALSXTWeaponReadyPositionTags::Hip, ALSXTWeaponReadyPositionTags::PatrolReady, ALSXTWeaponReadyPositionTags::HighReady, ALSXTWeaponReadyPositionTags::LowReady, ALSXTWeaponReadyPositionTags::Hidden };
	if (AlsxtCharacterPlayer->GetDesiredCombatStance() == ALSXTCombatStanceTags::Neutral)
	{
		AvailablePositions = {ALSXTWeaponReadyPositionTags::PatrolReady, ALSXTWeaponReadyPositionTags::HighReady, ALSXTWeaponReadyPositionTags::LowReady, ALSXTWeaponReadyPositionTags::Hidden };
	}
	else
	{
		AvailablePositions = { ALSXTWeaponReadyPositionTags::Ready, ALSXTWeaponReadyPositionTags::Retention, ALSXTWeaponReadyPositionTags::Hip, ALSXTWeaponReadyPositionTags::PatrolReady, ALSXTWeaponReadyPositionTags::HighReady, ALSXTWeaponReadyPositionTags::LowReady, ALSXTWeaponReadyPositionTags::Hidden };
	}
	int CurrentIndex = AvailablePositions.IndexOfByKey(AlsxtCharacterPlayer->GetDesiredWeaponReadyPosition());
	int NextIndex = (CurrentIndex + 1) > (AvailablePositions.Num() - 1) ? 0 : CurrentIndex + 1;

	// if ((CurrentIndex + 1) > (AvailablePositions.Num() - 1))
	// {
	// 	NextIndex = 0;
	// }
	// else
	// {
	// 	NextIndex = CurrentIndex + 1;
	// }
	AlsxtCharacterPlayer->SetDesiredWeaponReadyPosition(AvailablePositions[NextIndex]);
}

void AAlsxtPlayerController::Input_OnSwitchGripPosition()
{
	if (AlsxtCharacterPlayer->CanSwitchGripPosition())
	{
		FGameplayTagContainer AvailableGripPositions = AlsxtCharacterPlayer->GetAvailableGripPositions();
		TArray<FGameplayTag> AvailableGripPositionsArray;
		AvailableGripPositions.GetGameplayTagArray(AvailableGripPositionsArray);
		if (AvailableGripPositions.IsEmpty() || AvailableGripPositions.Num() == 1 && AvailableGripPositionsArray[0] == AlsxtCharacterPlayer->GetDesiredGripPosition())
		{
			return;
		}
		int LastIndex = AvailableGripPositionsArray.Num() - 1;
		int CurrentIndex = AvailableGripPositionsArray.IndexOfByKey(AlsxtCharacterPlayer->GetDesiredGripPosition());
		int NextIndex;
		if ((CurrentIndex + 1) > LastIndex)
		{
			NextIndex = 0;
		}
		else
		{
			NextIndex = CurrentIndex + 1;
		}

		AlsxtCharacterPlayer->SetDesiredGripPosition(AvailableGripPositionsArray[NextIndex]);
	}
}

void AAlsxtPlayerController::Input_OnSwitchForegripPosition()
{
	if (AlsxtCharacterPlayer->CanSwitchForegripPosition())
	{
		FGameplayTagContainer AvailableForegripPositions = AlsxtCharacterPlayer->GetAvailableForegripPositions();
		TArray<FGameplayTag> AvailableForegripPositionsArray;
		AvailableForegripPositions.GetGameplayTagArray(AvailableForegripPositionsArray);
		if (AvailableForegripPositions.IsEmpty() || AvailableForegripPositions.Num() == 1 && AvailableForegripPositionsArray[0] == AlsxtCharacterPlayer->GetDesiredGripPosition())
		{
			return;
		}
		int LastIndex = AvailableForegripPositionsArray.Num() - 1;
		int CurrentIndex = AvailableForegripPositionsArray.IndexOfByKey(AlsxtCharacterPlayer->GetDesiredForegripPosition());
		int NextIndex;
		if ((CurrentIndex + 1) > LastIndex)
		{
			NextIndex = 0;
		}
		else
		{
			NextIndex = CurrentIndex + 1;
		}
		
		AlsxtCharacterPlayer->SetDesiredForegripPosition(AvailableForegripPositionsArray[NextIndex]);
		FAlsxtHeldItemState NewHeldItemState = AlsxtCharacterPlayer->GetHeldItemState();
		NewHeldItemState.GripState.Foregrip.Grip = IAlsxtHeldItemInterface::Execute_GetHeldItemForegrip(this);
		AlsxtCharacterPlayer->SetHeldItemState(NewHeldItemState);
	}
}

void AAlsxtPlayerController::Input_OnToggleGait()
{
	if (AlsxtCharacterPlayer->CanToggleGait())
	{
		if ((AlsxtCharacterPlayer->GetDesiredGait() == AlsGaitTags::Walking))
		{
			AlsxtCharacterPlayer->SetDesiredGait(AlsGaitTags::Running);
		}
		else
		{
			AlsxtCharacterPlayer->SetDesiredGait(AlsGaitTags::Walking);
		}
	}
}

void AAlsxtPlayerController::Input_OnToggleCombatReady()
{
	if (AlsxtCharacterPlayer->CanToggleCombatReady())
	{
		if ((AlsxtCharacterPlayer->GetDesiredCombatStance() == FGameplayTag::EmptyTag) || (AlsxtCharacterPlayer->GetDesiredCombatStance() == ALSXTCombatStanceTags::Neutral))
		{
			if (AlsxtCharacterPlayer->CanBecomeCombatReady())
			{
				AlsxtCharacterPlayer->SetDesiredCombatStance(ALSXTCombatStanceTags::Ready);
				if (IAlsxtHeldItemInterface::Execute_IsHoldingAimableItem(this))
				{
					if (AlsxtCharacterPlayer->GetRotationMode() != AlsRotationModeTags::Aiming)
					{
						AlsxtCharacterPlayer->SetDesiredWeaponReadyPosition(ALSXTWeaponReadyPositionTags::LowReady);
					}
					else
					{
						AlsxtCharacterPlayer->SetDesiredWeaponReadyPosition(ALSXTWeaponReadyPositionTags::Ready);
					}
				}
				else
				{
					AlsxtCharacterPlayer->SetDesiredWeaponReadyPosition(ALSXTWeaponReadyPositionTags::Ready);
				}
			}
		}
		else
		{
			AlsxtCharacterPlayer->SetDesiredCombatStance(ALSXTCombatStanceTags::Neutral);
			AlsxtCharacterPlayer->SetDesiredWeaponReadyPosition(ALSXTWeaponReadyPositionTags::PatrolReady);
		}
	}
}