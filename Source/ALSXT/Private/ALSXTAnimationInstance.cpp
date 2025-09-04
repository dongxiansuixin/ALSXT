// Fill out your copyright notice in the Description page of Project Settings.

#include "ALSXTAnimationInstance.h"
#include "ALSXTAnimationInstanceProxy.h"
#include "ALSXTCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/AlsxtCharacterInterface.h"
#include "Interfaces/AlsxtHeldItemInterface.h"
#include "Utility/ALSXTConstants.h"
#include "ALS/Public/Utility/AlsMacros.h"
#include "Math/UnrealMathUtility.h"
#include "Stats/Stats.h"
#include "Interfaces/AlsxtFirearmInterface.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ALSXTAnimationInstance)

UALSXTAnimationInstance::UALSXTAnimationInstance()
{
	RootMotionMode = ERootMotionMode::RootMotionFromMontagesOnly;
}

void UALSXTAnimationInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ALSXTCharacter = Cast<AALSXTCharacter>(GetOwningActor());

#if WITH_EDITOR
	if (!GetWorld()->IsGameWorld() && !IsValid(ALSXTCharacter))
	{
		// Use default objects for editor preview.

		ALSXTCharacter = GetMutableDefault<AALSXTCharacter>();
	}
#endif
}

void UALSXTAnimationInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ALS_ENSURE(IsValid(ALSXTSettings));
	ALS_ENSURE(IsValid(ALSXTCharacter));
	if (GetOwningActor()->Implements<UAlsxtCharacterInterface>())
	{
		StaminaThresholdSettings = IAlsxtCharacterInterface::Execute_GetCharacterSettings(GetOwningActor())->StatusSettings.StaminaThresholdSettings;
		CharacterBreathEffectsSettings = IAlsxtCharacterInterface::Execute_GetCharacterSettings(GetOwningActor())->BreathEffects;
	}
}

void UALSXTAnimationInstance::NativeUpdateAnimation(const float DeltaTime)
{

	Super::NativeUpdateAnimation(DeltaTime);

	if (!IsValid(ALSXTCharacter))
	{
		return;
	}

	if (!GetOwningActor()->Implements<UAlsxtCharacterInterface>())
	{
		return;
	}

	RefreshALSXTPose();
	
	if (GetOwningActor()->Implements<UAlsxtCharacterInterface>())
	{
		JigglePhysicsSettings = IAlsxtCharacterInterface::Execute_GetCharacterJigglePhysicsSettings(GetOwningActor());
		Freelooking = IAlsxtCharacterInterface::Execute_GetCharacterFreelooking(GetOwningActor());
		Sex = IAlsxtCharacterInterface::Execute_GetCharacterSex(GetOwningActor());
		DefensiveMode = IAlsxtCharacterInterface::Execute_GetCharacterDefensiveMode(GetOwningActor());
		Lean = IAlsxtCharacterInterface::Execute_GetCharacterLean(GetOwningActor());
		LocomotionVariant = IAlsxtCharacterInterface::Execute_GetCharacterLocomotionVariant(GetOwningActor());
		Injury = IAlsxtCharacterInterface::Execute_GetCharacterInjury(GetOwningActor());
		CombatStance = IAlsxtCharacterInterface::Execute_GetCharacterCombatStance(GetOwningActor());
		WeaponFirearmStance = IAlsxtCharacterInterface::Execute_GetCharacterWeaponFirearmStance(GetOwningActor());
		WeaponReadyPosition = IAlsxtCharacterInterface::Execute_GetCharacterWeaponReadyPosition(GetOwningActor());
		StationaryMode = IAlsxtCharacterInterface::Execute_GetCharacterStationaryMode(GetOwningActor());
		HoldingBreath = IAlsxtCharacterInterface::Execute_GetCharacterHoldingBreath(GetOwningActor());
		IAlsxtCharacterInterface::Execute_GetCharacterGesture(GetOwningActor(), Gesture, GestureHand);
		ForegripPosition = IAlsxtCharacterInterface::Execute_GetCharacterForegripPosition(GetOwningActor());
		FirearmFingerAction = IAlsxtCharacterInterface::Execute_GetCharacterFirearmFingerAction(GetOwningActor());
		FirearmFingerActionHand = IAlsxtCharacterInterface::Execute_GetCharacterFirearmFingerActionHand(GetOwningActor());
		WeaponCarryPosition = IAlsxtCharacterInterface::Execute_GetCharacterWeaponCarryPosition(GetOwningActor());
		FirearmSightLocation = IAlsxtCharacterInterface::Execute_GetCharacterFirearmSightLocation(GetOwningActor());
		ForegripTransform = IAlsxtCharacterInterface::Execute_GetCharacterCurrentForegripTransform(GetOwningActor());
		VaultType = IAlsxtCharacterInterface::Execute_GetCharacterVaultType(GetOwningActor());		
		AimState = IAlsxtCharacterInterface::Execute_GetCharacterAimState(GetOwningActor());
		FreelookState = IAlsxtCharacterInterface::Execute_GetCharacterFreelookState(GetOwningActor());
		HeadLookAtState = IAlsxtCharacterInterface::Execute_GetCharacterHeadLookAtState(GetOwningActor());
		StatusState = IAlsxtCharacterInterface::Execute_GetStatusState(GetOwningActor());
		DefensiveModeState = IAlsxtCharacterInterface::Execute_GetCharacterDefensiveModeState(GetOwningActor());
		DefensiveModeAnimations = IAlsxtCharacterInterface::Execute_GetCharacterDefensiveModeAnimations(GetOwningActor());
		StationaryModeState = IAlsxtCharacterInterface::Execute_GetCharacterStationaryModeState(GetOwningActor());
		WeaponObstruction = IAlsxtCharacterInterface::Execute_GetCharacterWeaponObstruction(GetOwningActor());
		BreathState = IAlsxtCharacterInterface::Execute_GetCharacterBreathState(GetOwningActor());
		// ReloadingType = IALSXTCharacterInterface::Execute_GetCharacterReloadingType(GetOwningActor());
		
	}

	if (GetOwningActor()->Implements<UAlsxtCollisionInterface>())
	{
		PhysicalAnimationMode = IAlsxtCollisionInterface::Execute_GetCharacterPhysicalAnimationMode(GetOwningActor());
		CrowdNavigationPoseState = IAlsxtCollisionInterface::Execute_GetCrowdNavigationPoseState(GetOwningActor());
		BumpPoseState = IAlsxtCollisionInterface::Execute_GetBumpPoseState(GetOwningActor());
	}

	if (GetOwningActor()->Implements<UAlsxtHeldItemInterface>())
	{
		HeldItemSettings = IAlsxtHeldItemInterface::Execute_GetHeldItemSettings(GetOwningActor());
		HeldItemState = IAlsxtHeldItemInterface::Execute_GetCharacterHeldItemState(GetOwningActor());
		DoesOverlayObjectUseLeftHandIK = IAlsxtHeldItemInterface::Execute_GetHeldItemSettings(GetOwningActor()).UsesLeftHandIK;
	}

	if (GetOwningActor()->Implements<UAlsxtFirearmInterface>())
	{
		if (IsValid(IAlsxtFirearmInterface::Execute_GetFirearmDischargeEffectsState(GetOwningActor()).RecoilAsset))
		{
			RecoilState = IAlsxtFirearmInterface::Execute_GetRecoilState(GetOwningActor());
		}


	}

	if (IAlsxtCharacterInterface::Execute_GetCharacterStationaryModeState(GetOwningActor()).Mode != StationaryModeState.Mode && (IAlsxtCharacterInterface::Execute_GetCharacterStance(GetOwningActor()) != Stance || IAlsxtCharacterInterface::Execute_GetCharacterCombatStance(GetOwningActor()) != CombatStance))
	{

	}

	// for (FALSXTStationaryModeEntry StationaryModeAnimations : ALSXTSettings->StationaryMode.Animations)
	// {
	// 	FGameplayTagContainer CurrentStateContainer;
	// 	CurrentStateContainer.AddTag(IALSXTCharacterInterface::Execute_GetCharacterOverlayMode(GetOwningActor()));
	// 	CurrentStateContainer.AddTag(IALSXTCharacterInterface::Execute_GetCharacterStance(GetOwningActor()));
	// 	FGameplayTagContainer EntryContainer;
	// 	if (StationaryModeAnimations.Overlays.HasTag(IALSXTCharacterInterface::Execute_GetCharacterOverlayMode(GetOwningActor())))
	// 	{
	// 
	// 	}
	// }
}

void UALSXTAnimationInstance::NativeThreadSafeUpdateAnimation(const float DeltaTime)
{

	Super::NativeThreadSafeUpdateAnimation(DeltaTime);

	if (!IsValid(ALSXTSettings) || !IsValid(ALSXTCharacter))
	{
		return;
	}
}

void UALSXTAnimationInstance::NativePostEvaluateAnimation()
{

	Super::NativePostEvaluateAnimation();

	if (!IsValid(ALSXTSettings) || !IsValid(ALSXTCharacter))
	{
		return;
	}

	bPendingUpdate = false;
}

FAnimInstanceProxy* UALSXTAnimationInstance::CreateAnimInstanceProxy()
{
	return new FALSXTAnimationInstanceProxy{ this };
}

bool UALSXTAnimationInstance::IsSpineRotationAllowed()
{
	if (GetOwningActor()->Implements<UAlsxtCharacterInterface>())
	{
		return Super::IsSpineRotationAllowed() && IAlsxtCharacterInterface::Execute_GetCharacterFreelooking(GetOwningActor()) != ALSXTFreelookingTags::True;
		//return ALSXTCharacter->GetRotationMode() == AlsRotationModeTags::Aiming && ALSXTCharacter->GetLocomotionState().bRotationLocked == false;
	}
	else
	{
		return false;
	}
}

bool UALSXTAnimationInstance::IsRotateInPlaceAllowed()
{
	if (GetOwningActor()->Implements<UAlsxtCharacterInterface>())
	{
		return Super::IsRotateInPlaceAllowed() && IAlsxtCharacterInterface::Execute_GetCharacterFreelooking(GetOwningActor()) != ALSXTFreelookingTags::True;
	}
	else
	{
		return false;
	}
}

bool UALSXTAnimationInstance::IsTurnInPlaceAllowed()
{
	if (GetOwningActor()->Implements<UAlsxtCharacterInterface>())
	{
		return Super::IsTurnInPlaceAllowed() && IAlsxtCharacterInterface::Execute_GetCharacterFreelooking(GetOwningActor()) != ALSXTFreelookingTags::True;
	}
	else
	{
		return false;
	}
}

void UALSXTAnimationInstance::RefreshALSXTPose()
{
	const auto& Curves{ GetProxyOnAnyThread<FALSXTAnimationInstanceProxy>().GetAnimationCurves(EAnimCurveType::AttributeCurve) };

	static const auto GetCurveValue{
		[](const TMap<FName, float>& Curves, const FName& CurveName) -> float
		{
			const auto* Value{Curves.Find(CurveName)};

			return Value != nullptr ? *Value : 0.0f;
		}
	};

	if (GetOwningActor()->Implements<UAlsxtCharacterInterface>())
	{
		ALSXTPoseState.LeanDirection = IAlsxtCharacterInterface::Execute_GetCharacterPoseState(GetOwningActor()).LeanDirection;
	}

	ALSXTPoseState.LeanLeftAmount = GetCurveValue(Curves, UALSXTConstants::PoseLeanLeftCurveName());
	ALSXTPoseState.LeanRightAmount = GetCurveValue(Curves, UALSXTConstants::PoseLeanRightCurveName());

	ALSXTPoseState.CantedAmount = GetCurveValue(Curves, UALSXTConstants::PoseCantedCurveName());

	ALSXTPoseState.VaultingAmount = GetCurveValue(Curves, UALSXTConstants::PoseVaultingCurveName());
	ALSXTPoseState.SlidingAmount = GetCurveValue(Curves, UALSXTConstants::PoseSlidingCurveName());

	ALSXTPoseState.WallJumpAmount = GetCurveValue(Curves, UALSXTConstants::PoseWallJumpCurveName());
	ALSXTPoseState.WallRunAmount = GetCurveValue(Curves, UALSXTConstants::PoseWallRunCurveName());

	ALSXTPoseState.StationaryAmount = GetCurveValue(Curves, UALSXTConstants::PoseStationaryCurveName());
	ALSXTPoseState.SeatedAmount = GetCurveValue(Curves, UALSXTConstants::PoseSeatedCurveName());

	// Use the grounded pose curve value to "unweight" the gait pose curve. This is used to
	// instantly get the full gait value from the very beginning of transitions to grounded states.

	// PoseState.UnweightedGaitAmount = PoseState.GroundedAmount > 0.0f
	// 	? PoseState.GaitAmount / PoseState.GroundedAmount
	// 	: PoseState.GaitAmount;
	// 
	// PoseState.UnweightedGaitWalkingAmount = UAlsMath::Clamp01(PoseState.UnweightedGaitAmount);
	// PoseState.UnweightedGaitRunningAmount = UAlsMath::Clamp01(PoseState.UnweightedGaitAmount - 1.0f);
	// PoseState.UnweightedGaitSprintingAmount = UAlsMath::Clamp01(PoseState.UnweightedGaitAmount - 2.0f);
}

void UALSXTAnimationInstance::UpdateStatusState()
{
	if (GetOwningActor()->Implements<UAlsxtCharacterInterface>())
	{
		FAlsxtStatusState NewStatusState{ IAlsxtCharacterInterface::Execute_GetStatusState(GetOwningActor()) };

		if (NewStatusState != StatusState)
		{
			StatusState = NewStatusState;
		}
	}
}

FALSXTControlRigInput UALSXTAnimationInstance::GetALSXTControlRigInput() const {

	return {
		.bObstacleNavigation = DefensiveModeState.ObstacleMode == ALSXTDefensiveModeTags::CrowdNavigation || DefensiveModeState.ObstacleMode == ALSXTDefensiveModeTags::ObstacleNavigation,
		.bCombatStance = CombatStance != ALSXTCombatStanceTags::Neutral,
		.bEnableLeftHandIK = DoesOverlayObjectUseLeftHandIK
	};
}
