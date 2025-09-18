// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).


#include "AlsxtCharacterPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/Data/AlsxtGasGameplayTags.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Utility/AlsVector.h"


/**
* @file AlsxtCharacterPlayer.cpp
* @brief template class that contains all shared Logic and Data for Player Classes.
* AAlsxtCharacterPlayer depends on AAlsxtPlayerState and AAlsxtPlayerController to function.
* Create a Blueprint class based on this class, do not use the C++ class directly in the Editor
*/

void AAlsxtCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	
	// Set a Soft Object Pointer to the Player State
	if (const APlayerController* CurrentPlayerController = Cast<APlayerController>(GetController()))
	{
		if (CurrentPlayerController->PlayerState)
		{
			PlayerState = CurrentPlayerController->PlayerState;
		}
	}
	
}

void AAlsxtCharacterPlayer::SetupPlayerInputComponent(UInputComponent* Input)
{
	// Super::SetupPlayerInputComponent(Input);

	auto* EnhancedInput{Cast<UEnhancedInputComponent>(Input)};
	if (IsValid(EnhancedInput))
	{
		EnhancedInput->BindAction(LookMouseAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLookMouse);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLook);
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnMove);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSprint);
		EnhancedInput->BindAction(WalkAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnWalk);
		EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnCrouch);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnJump);
		EnhancedInput->BindAction(MantleAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnMantle);
		EnhancedInput->BindAction(AimAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnAim);
		EnhancedInput->BindAction(AimToggleAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnToggleAim);
		EnhancedInput->BindAction(FocusAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnFocus);
		EnhancedInput->BindAction(RagdollAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRagdoll);
		EnhancedInput->BindAction(RollAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRoll);
		EnhancedInput->BindAction(RotationModeAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnRotationMode);
		EnhancedInput->BindAction(ViewModeAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnViewMode);
		EnhancedInput->BindAction(SwitchShoulderAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSwitchShoulder);
		EnhancedInput->BindAction(LeanLeftAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLeanLeft);
		EnhancedInput->BindAction(ToggleLeanLeftAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLeanLeft);
		EnhancedInput->BindAction(LeanRightAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLeanRight);
		EnhancedInput->BindAction(ToggleLeanRightAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnLeanRight);
		EnhancedInput->BindAction(FreelookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnFreelook);
		EnhancedInput->BindAction(ToggleFreelookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnFreelook);
		EnhancedInput->BindAction(ToggleGaitAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnToggleGait);
		EnhancedInput->BindAction(ToggleCombatReadyAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnToggleCombatReady);
		EnhancedInput->BindAction(PrimaryInteractionAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnPrimaryInteraction);
		EnhancedInput->BindAction(SecondaryInteractionAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSecondaryInteraction);
		EnhancedInput->BindAction(BlockAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnBlock);
		EnhancedInput->BindAction(SwitchWeaponReadyPositionAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSwitchWeaponReadyPosition);
		EnhancedInput->BindAction(SwitchGripPositionAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSwitchGripPosition);
		EnhancedInput->BindAction(SwitchForegripPositionAction, ETriggerEvent::Triggered, this, &ThisClass::Input_OnSwitchForegripPosition);

		InputMantleValue = EnhancedInput->GetBoundActionValue(MantleAction);
		
		OnSetupPlayerInputComponentUpdated.Broadcast();
	}
}

// Server only
void AAlsxtCharacterPlayer::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	// AAlsxtPlayerState* PS = GetPlayerState<AAlsxtPlayerState>();
	// if (PS)
	// {
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		// AbilitySystemComponent = Cast<UAlsxtAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		// PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		// Set the AttributeSetBase for convenience attribute functions
		// AttributeSetBase = PS->GetAttributeSetBase();

		// If we handle players disconnecting and rejoining in the future, we'll have to change this so that possession from rejoining doesn't reset attributes.
		// For now assume possession = spawn/respawn.
		// InitializeAttributes();

		
		// Respawn specific things that won't affect first possession.

		// Forcibly set the DeadTag count to 0
		// AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

		// Set Health/Mana/Stamina to their max. This is only necessary for *Respawn*.
		// SetHealth(GetMaxHealth());
		// SetMana(GetMaxMana());
		// SetStamina(GetMaxStamina());

		// End respawn specific things


		// AddStartupEffects();

		// AddCharacterAbilities();

		// AGDPlayerController* PC = Cast<AGDPlayerController>(GetController());
		// if (PC)
		// {
		// 	PC->CreateHUD();
		// }
// 
		// InitializeFloatingStatusBar();
	// }
}

UAbilitySystemComponent* AAlsxtCharacterPlayer::GetAbilitySystemComponent() const
{
	if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetPlayerState()))
	{
		return AbilitySystemInterface->GetAbilitySystemComponent();
	}
	else
	{
		return nullptr;
	}
}

void AAlsxtCharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	AAlsxtPlayerState* PS = GetPlayerState<AAlsxtPlayerState>();
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	}
}

void AAlsxtCharacterPlayer::Input_OnLookMouse(const FInputActionValue& ActionValue)
{
	const FVector2f Value{ActionValue.Get<FVector2D>()};

	AddControllerPitchInput(Value.Y * LookUpMouseSensitivity);
	AddControllerYawInput(Value.X * LookRightMouseSensitivity);
}

void AAlsxtCharacterPlayer::Input_OnLook(const FInputActionValue& ActionValue)
{
	const FVector2f Value{ActionValue.Get<FVector2D>()};

	AddControllerPitchInput(Value.Y * LookUpRate);
	AddControllerYawInput(Value.X * LookRightRate);
}

void AAlsxtCharacterPlayer::Input_OnMove(const FInputActionValue& ActionValue)
{
	const auto Value{UAlsVector::ClampMagnitude012D(ActionValue.Get<FVector2D>())};

	auto ViewRotation{GetViewState().Rotation};

	if (IsValid(GetController()))
	{
		// Use exact camera rotation instead of target rotation whenever possible.

		FVector ViewLocation;
		GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}

	const auto ForwardDirection{UAlsVector::AngleToDirectionXY(UE_REAL_TO_FLOAT(ViewRotation.Yaw))};
	const auto RightDirection{UAlsVector::PerpendicularCounterClockwiseXY(ForwardDirection)};

	AddMovementInput(ForwardDirection * Value.Y + RightDirection * Value.X);
}

void AAlsxtCharacterPlayer::Input_OnSprint(const FInputActionValue& ActionValue)
{
	if (GetAbilitySystemComponent())
	{
		FGameplayTagContainer SprintGameplayTags;
		// SprintGameplayTags.AddTag(ALSXTAbilityGameplayTags::Sprint);
		SprintGameplayTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Gameplay.Ability.Sprint")));
		if (ActionValue.Get<bool>() && GetAbilitySystemComponent()->TryActivateAbilitiesByTag(SprintGameplayTags, true))
		{
			// GetAbilitySystemComponent()->TryActivateAbilitiesByTag(SprintGameplayTags);
			// GetAbilitySystemComponent()->TryActivateAbility(SprintHandle);
			// GetAbilitySystemComponent()->Activa
		}
		else
		{
			// GetAbilitySystemComponent()->CancelAbilities(SprintGameplayTagsPtr,nullptr, nullptr);
			GetAbilitySystemComponent()->CancelAbilities(&SprintGameplayTags);
			UE_LOG(LogTemp, Warning, TEXT("TryActivateAbilitiesByTag failed!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetAbilitySystemComponent failed!"));
	}
}

void AAlsxtCharacterPlayer::Input_OnWalk()
{
	if (GetDesiredGait() == AlsGaitTags::Walking)
	{
		SetDesiredGait(AlsGaitTags::Running);
	}
	else if (GetDesiredGait() == AlsGaitTags::Running)
	{
		SetDesiredGait(AlsGaitTags::Walking);
	}
}

void AAlsxtCharacterPlayer::Input_OnCrouch()
{
	if (GetDesiredStance() == AlsStanceTags::Standing)
	{
		if (CanSlide())
		{
			TryStartSliding(1.3f);
		}
		else {
			SetDesiredStance(AlsStanceTags::Crouching);
		}
	}
	else if (GetDesiredStance() == AlsStanceTags::Crouching)
	{
		SetDesiredStance(AlsStanceTags::Standing);
		if (GetDesiredStatus() != ALSXTStatusTags::Normal)
		{
			SetDesiredStatus(ALSXTStatusTags::Normal);
		}
	}
}

void AAlsxtCharacterPlayer::Input_OnJump(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		if (StopRagdolling())
		{
			return;
		}

		if (StartMantlingGrounded())
		{
			return;
		}

		if (GetStance() == AlsStanceTags::Crouching)
		{
			SetDesiredStance(AlsStanceTags::Standing);
			return;
		}

		Jump();
	}
	else
	{
		StopJumping();
	}
}

void AAlsxtCharacterPlayer::Input_OnAim(const FInputActionValue& ActionValue)
{
	SetDesiredAiming(ActionValue.Get<bool>());
}

void AAlsxtCharacterPlayer::Input_OnRagdoll()
{
	if (!StopRagdolling())
	{
		StartRagdolling();
	}
}

void AAlsxtCharacterPlayer::Input_OnRoll()
{
	static constexpr auto PlayRate{1.3f};

	StartRolling(PlayRate);
}

void AAlsxtCharacterPlayer::Input_OnRotationMode()
{
	SetDesiredRotationMode(GetDesiredRotationMode() == AlsRotationModeTags::VelocityDirection
							   ? AlsRotationModeTags::ViewDirection
							   : AlsRotationModeTags::VelocityDirection);
}

void AAlsxtCharacterPlayer::Input_OnViewMode()
{
	SetViewMode(GetViewMode() == AlsViewModeTags::ThirdPerson ? AlsViewModeTags::FirstPerson : AlsViewModeTags::ThirdPerson);
}

void AAlsxtCharacterPlayer::Input_OnSwitchShoulder()
{
	Camera->SetRightShoulder(!Camera->IsRightShoulder());
}

void AAlsxtCharacterPlayer::Input_OnMantle(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		// RefreshMantle();
	}
	else
	{

	}
}

void AAlsxtCharacterPlayer::Input_OnToggleAim()
{
	if (IAlsxtHeldItemInterface::Execute_IsHoldingAimableItem(this)) 
	{
		if (GetDesiredRotationMode() == AlsRotationModeTags::Aiming)
		{
			SetDesiredRotationMode(AlsRotationModeTags::ViewDirection);
			SetDesiredCombatStance(ALSXTCombatStanceTags::Ready);
		}
		if (CanAim())
		{
			SetViewMode(AlsViewModeTags::FirstPerson);
			SetDesiredCombatStance(ALSXTCombatStanceTags::Aiming);
			SetDesiredRotationMode(AlsRotationModeTags::Aiming);
		}
	}
}

void AAlsxtCharacterPlayer::Input_OnFocus(const FInputActionValue& ActionValue)
{
	if (CanFocus())
	{
		if (ActionValue.Get<bool>())
		{
			SetDesiredFocus(ALSXTFocusedTags::True);
		}
		else
		{
			SetDesiredFocus(ALSXTFocusedTags::False);
		}
	}
}

void AAlsxtCharacterPlayer::Input_OnFreelook(const FInputActionValue& ActionValue)
{
	if (CanFreelook())
	{
		if (ActionValue.Get<bool>())
		{
			// ActivateFreelooking();
		}
		else
		{
			// DeactivateFreelooking();
		}
	}
}

void AAlsxtCharacterPlayer::Input_OnToggleGait()
{
	if (CanToggleGait())
	{
		if ((GetDesiredGait() == AlsGaitTags::Walking))
		{
			SetDesiredGait(AlsGaitTags::Running);
		}
		else
		{
			SetDesiredGait(AlsGaitTags::Walking);
		}
	}
}

void AAlsxtCharacterPlayer::Input_OnToggleCombatReady()
{
	if (CanToggleCombatReady())
	{
		if ((GetDesiredCombatStance() == FGameplayTag::EmptyTag) || (GetDesiredCombatStance() == ALSXTCombatStanceTags::Neutral))
		{
			if (CanBecomeCombatReady())
			{
				SetDesiredCombatStance(ALSXTCombatStanceTags::Ready);
				if (IAlsxtHeldItemInterface::Execute_IsHoldingAimableItem(this))
				{
					if (GetRotationMode() != AlsRotationModeTags::Aiming)
					{
						SetDesiredWeaponReadyPosition(ALSXTWeaponReadyPositionTags::LowReady);
					}
					else
					{
						SetDesiredWeaponReadyPosition(ALSXTWeaponReadyPositionTags::Ready);
					}
				}
				else
				{
					SetDesiredWeaponReadyPosition(ALSXTWeaponReadyPositionTags::Ready);
				}
			}
		}
		else
		{
			SetDesiredCombatStance(ALSXTCombatStanceTags::Neutral);
			SetDesiredWeaponReadyPosition(ALSXTWeaponReadyPositionTags::PatrolReady);
		}
	}
}

void AAlsxtCharacterPlayer::Input_OnBlock(const FInputActionValue& ActionValue)
{
	FAlsxtDefensiveModeState PreviousDefensiveModeState = GetDefensiveModeState();

	if (CanEnterBlockingDefensiveMode())
	{
		if (ActionValue.Get<bool>() == true)
		{
			FAlsxtDefensiveModeState NewDefensiveModeState = GetDefensiveModeState();
			NewDefensiveModeState.Mode = ALSXTDefensiveModeTags::Anticipation;
			NewDefensiveModeState.AnticipationMode = ALSXTDefensiveModeTags::Anticipation;
			NewDefensiveModeState.AnticipationSide = PreviousDefensiveModeState.AnticipationSide == FGameplayTag::EmptyTag ? ALSXTImpactSideTags::Front : PreviousDefensiveModeState.AnticipationSide;
			NewDefensiveModeState.AnticipationHeight = PreviousDefensiveModeState.AnticipationHeight == FGameplayTag::EmptyTag ? ALSXTImpactHeightTags::Middle : PreviousDefensiveModeState.AnticipationHeight;
			NewDefensiveModeState.ObstacleMode = FGameplayTag::EmptyTag;
			NewDefensiveModeState.ObstacleSide = FGameplayTag::EmptyTag;
			NewDefensiveModeState.ObstacleHeight = FGameplayTag::EmptyTag;
			SetDefensiveModeState(NewDefensiveModeState);
			// SetDesiredDefensiveMode(ALSXTDefensiveModeTags::Blocking);

		}
		else 
		{
			// ResetDefensiveModeState();
			FAlsxtDefensiveModeState NewDefensiveModeState = GetDefensiveModeState();
			NewDefensiveModeState.Mode = PreviousDefensiveModeState.Mode == ALSXTDefensiveModeTags::Anticipation ? FGameplayTag::EmptyTag : PreviousDefensiveModeState.Mode;
			NewDefensiveModeState.AnticipationMode = FGameplayTag::EmptyTag;
			NewDefensiveModeState.AnticipationSide = FGameplayTag::EmptyTag;
			NewDefensiveModeState.AnticipationHeight = FGameplayTag::EmptyTag;
			NewDefensiveModeState.ObstacleMode = FGameplayTag::EmptyTag;
			NewDefensiveModeState.ObstacleSide = FGameplayTag::EmptyTag;
			NewDefensiveModeState.ObstacleHeight = FGameplayTag::EmptyTag;
			SetDefensiveModeState(NewDefensiveModeState);
			// SetDesiredDefensiveMode(FGameplayTag::EmptyTag);
		}
	}
	else if ((DesiredDefensiveMode == ALSXTDefensiveModeTags::Blocking) && (ActionValue.Get<bool>()  == false))
	{
		FAlsxtDefensiveModeState NewDefensiveModeState = GetDefensiveModeState();
		NewDefensiveModeState.Mode = PreviousDefensiveModeState.Mode == ALSXTDefensiveModeTags::Anticipation ? FGameplayTag::EmptyTag : PreviousDefensiveModeState.Mode;
		NewDefensiveModeState.AnticipationMode = FGameplayTag::EmptyTag;
		NewDefensiveModeState.AnticipationSide = FGameplayTag::EmptyTag;
		NewDefensiveModeState.AnticipationHeight = FGameplayTag::EmptyTag;
		NewDefensiveModeState.ObstacleMode = FGameplayTag::EmptyTag;
		NewDefensiveModeState.ObstacleSide = FGameplayTag::EmptyTag;
		NewDefensiveModeState.ObstacleHeight = FGameplayTag::EmptyTag;
		SetDefensiveModeState(NewDefensiveModeState);
		SetDesiredDefensiveMode(FGameplayTag::EmptyTag);
	}
}

void AAlsxtCharacterPlayer::Input_OnLeanLeft(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		if (CanLean())
		{
			SetDesiredLean(ALSXTLeanDirectionTags::Left);
			FAlsxtPoseState NewPoseState = GetALSXTPoseState();
			NewPoseState.LeanDirection = ALSXTLeanDirectionTags::Left;
			SetALSXTPoseState(NewPoseState);
		}
	}
	else
	{
		SetDesiredLean(FGameplayTag::EmptyTag);
		FAlsxtPoseState NewPoseState = GetALSXTPoseState();
		NewPoseState.LeanDirection = FGameplayTag::EmptyTag;
		SetALSXTPoseState(NewPoseState);
	}
}

void AAlsxtCharacterPlayer::Input_OnLeanRight(const FInputActionValue& ActionValue)
{
	if (ActionValue.Get<bool>())
	{
		if (CanLean())
		{
			SetDesiredLean(ALSXTLeanDirectionTags::Right);
			FAlsxtPoseState NewPoseState = GetALSXTPoseState();
			NewPoseState.LeanDirection = ALSXTLeanDirectionTags::Right;
			SetALSXTPoseState(NewPoseState);
		}
	}
	else
	{
		SetDesiredLean(FGameplayTag::EmptyTag);
		FAlsxtPoseState NewPoseState = GetALSXTPoseState();
		NewPoseState.LeanDirection = FGameplayTag::EmptyTag;
		SetALSXTPoseState(NewPoseState);
	}
}

void AAlsxtCharacterPlayer::Input_OnSwitchWeaponFirearmStance()
{
	if (GetDesiredCombatStance() == ALSXTCombatStanceTags::Neutral)
	{
		return;
	}
	else
	{
		FGameplayTagContainer AvailableStances = GetAvailableFirearmStances();
		TArray<FGameplayTag> AvailableStancesArray;
		AvailableStances.GetGameplayTagArray(AvailableStancesArray);
		if (AvailableStances.Num() <= 0 || AvailableStances.Num() == 1 && AvailableStancesArray[0] == GetDesiredWeaponFirearmStance())
		{
			return;
		}
		int CurrentIndex = AvailableStancesArray.IndexOfByKey(GetDesiredWeaponFirearmStance());
		int NextIndex;
		if ((CurrentIndex + 1) > (AvailableStancesArray.Num() - 1))
		{
			NextIndex = 0;
		}
		else
		{
			NextIndex = CurrentIndex + 1;
		}
		SetDesiredWeaponFirearmStance(AvailableStancesArray[NextIndex]);
	}
}

void AAlsxtCharacterPlayer::Input_OnSwitchWeaponReadyPosition()
{
	TArray<FGameplayTag> AvailablePositions;
	// TArray<FGameplayTag> AvailablePositions = (GetDesiredCombatStance() == ALSXTCombatStanceTags::Neutral) ? {ALSXTWeaponReadyPositionTags::PatrolReady, ALSXTWeaponReadyPositionTags::HighReady, ALSXTWeaponReadyPositionTags::LowReady, ALSXTWeaponReadyPositionTags::Hidden } : { ALSXTWeaponReadyPositionTags::Ready, ALSXTWeaponReadyPositionTags::Retention, ALSXTWeaponReadyPositionTags::Hip, ALSXTWeaponReadyPositionTags::PatrolReady, ALSXTWeaponReadyPositionTags::HighReady, ALSXTWeaponReadyPositionTags::LowReady, ALSXTWeaponReadyPositionTags::Hidden };
	if (GetDesiredCombatStance() == ALSXTCombatStanceTags::Neutral)
	{
		AvailablePositions = {ALSXTWeaponReadyPositionTags::PatrolReady, ALSXTWeaponReadyPositionTags::HighReady, ALSXTWeaponReadyPositionTags::LowReady, ALSXTWeaponReadyPositionTags::Hidden };
	}
	else
	{
		AvailablePositions = { ALSXTWeaponReadyPositionTags::Ready, ALSXTWeaponReadyPositionTags::Retention, ALSXTWeaponReadyPositionTags::Hip, ALSXTWeaponReadyPositionTags::PatrolReady, ALSXTWeaponReadyPositionTags::HighReady, ALSXTWeaponReadyPositionTags::LowReady, ALSXTWeaponReadyPositionTags::Hidden };
	}
	int CurrentIndex = AvailablePositions.IndexOfByKey(GetDesiredWeaponReadyPosition());
	int NextIndex = (CurrentIndex + 1) > (AvailablePositions.Num() - 1) ? 0 : CurrentIndex + 1;

	// if ((CurrentIndex + 1) > (AvailablePositions.Num() - 1))
	// {
	// 	NextIndex = 0;
	// }
	// else
	// {
	// 	NextIndex = CurrentIndex + 1;
	// }
	SetDesiredWeaponReadyPosition(AvailablePositions[NextIndex]);
}

void AAlsxtCharacterPlayer::Input_OnSwitchGripPosition()
{
	if (CanSwitchGripPosition())
	{
		FGameplayTagContainer AvailableGripPositions = GetAvailableGripPositions();
		TArray<FGameplayTag> AvailableGripPositionsArray;
		AvailableGripPositions.GetGameplayTagArray(AvailableGripPositionsArray);
		if (AvailableGripPositions.IsEmpty() || AvailableGripPositions.Num() == 1 && AvailableGripPositionsArray[0] == GetDesiredGripPosition())
		{
			return;
		}
		int LastIndex = AvailableGripPositionsArray.Num() - 1;
		int CurrentIndex = AvailableGripPositionsArray.IndexOfByKey(GetDesiredGripPosition());
		int NextIndex;
		if ((CurrentIndex + 1) > LastIndex)
		{
			NextIndex = 0;
		}
		else
		{
			NextIndex = CurrentIndex + 1;
		}

		SetDesiredGripPosition(AvailableGripPositionsArray[NextIndex]);
	}
}

void AAlsxtCharacterPlayer::Input_OnSwitchForegripPosition()
{
	if (CanSwitchForegripPosition())
	{
		FGameplayTagContainer AvailableForegripPositions = GetAvailableForegripPositions();
		TArray<FGameplayTag> AvailableForegripPositionsArray;
		AvailableForegripPositions.GetGameplayTagArray(AvailableForegripPositionsArray);
		if (AvailableForegripPositions.IsEmpty() || AvailableForegripPositions.Num() == 1 && AvailableForegripPositionsArray[0] == GetDesiredGripPosition())
		{
			return;
		}
		int LastIndex = AvailableForegripPositionsArray.Num() - 1;
		int CurrentIndex = AvailableForegripPositionsArray.IndexOfByKey(GetDesiredForegripPosition());
		int NextIndex;
		if ((CurrentIndex + 1) > LastIndex)
		{
			NextIndex = 0;
		}
		else
		{
			NextIndex = CurrentIndex + 1;
		}
		
		SetDesiredForegripPosition(AvailableForegripPositionsArray[NextIndex]);
		FAlsxtHeldItemState NewHeldItemState = GetHeldItemState();
		NewHeldItemState.GripState.Foregrip.Grip = IAlsxtHeldItemInterface::Execute_GetHeldItemForegrip(this);
		SetHeldItemState(NewHeldItemState);
	}
}

