#pragma once

#include "Engine/EngineTypes.h"
#include "Curves/CurveVector.h"
#include "AlsxtCameraAnimationInstanceSettings.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ALSXT_API UAlsxtGeneralCameraAnimationInstanceSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Features")
	bool bEnableThirdPersonCameraDroneMovementAnimation { true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Drone Movement Animation")
	UCurveVector* DefaultThirdPersonCameraDroneMovementAnimationCurve {nullptr};

};

UCLASS(Blueprintable, BlueprintType)
class ALSXT_API UAlsxtCameraAnimationInstanceSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Depth Of Field")
	UCurveVector* ThirdPersonCameraDroneMovementAnimationCurve {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Features")
	float CurveAlpha { 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Features")
	float WindResistance { 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Features")
	float DamageResistance { 0.5f };

};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtCameraAnimationInstanceState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Features")
	bool bEnableThirdPersonCameraDroneMovementAnimation { true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Depth Of Field")
	UCurveVector* CurrentAnimationCurve {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Features")
	float CurrentCurveAlpha { 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Features")
	float CurrentWindResistance { 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Features")
	float CurrentDamageResistance { 0.5f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Features")
	float CurrentDamage { 0.0f };

};
