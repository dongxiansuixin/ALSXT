#pragma once

#include "GameplayTagContainer.h"
#include "Camera/CameraShakeBase.h"
#include "Animation/AnimInstance.h"
#include "AlsxtOverlaySettings.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtCameraShakeSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseMagnitude{ 1.0f };
};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtOverlayCameraShakeSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseCameraShakeForOverlayMode{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtCameraShakeSetting WalkingCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtCameraShakeSetting RunningCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtCameraShakeSetting SprintingCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtCameraShakeSetting CrouchWalkingCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtCameraShakeSetting CrouchRunningCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtCameraShakeSetting ProneWalkingCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtCameraShakeSetting ProneRunningCameraShake;
};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtOverlaySettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.OverlayMode"))
	TMap<FGameplayTag, TSubclassOf<UAnimInstance>> OverlayAnimationInstanceClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer AimableOverlayModes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseGunBoneForOverlayObjects {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer LeftIKOverlayModes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, FAlsxtOverlayCameraShakeSettings> CameraShake;
};
