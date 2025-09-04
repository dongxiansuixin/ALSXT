#pragma once

#include "Engine/DataAsset.h"
#include "Engine/EngineTypes.h"
#include "Utility/ALSXTStructs.h"
#include "Settings/AlsMantlingSettings.h"
#include "AlsxtMantlingSettings.generated.h"

class UAnimMontage;
class UCurveFloat;
class UCurveVector;

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtMantlingParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	TWeakObjectPtr<UPrimitiveComponent> TargetPrimitive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FVector_NetQuantize100 TargetRelativeLocation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FRotator TargetRelativeRotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceUnits = "cm"))
	float MantlingHeight{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FGameplayTag LocomotionMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FGameplayTag Gait;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FGameplayTag MantlingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FVaultAnimation VaultAnimation;
};

UCLASS(Blueprintable, BlueprintType)
class ALSXT_API UAlsxtMantlingSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	UAlsMantlingSettings* AlsMantlingSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FVector2D FirstPersonYawRange {-180.0f, 180.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FVector2D FirstPersonPitchRange {-180.0f, 180.0f};

public:
	float GetStartTimeForHeight(FVector2D ReferenceHeight, FVector2D StartTime, float MantlingHeight) const;

	float GetPlayRateForHeight(FVector2D ReferenceHeight, FVector2D PlayRate, float MantlingHeight) const;
};

inline float UAlsxtMantlingSettings::GetStartTimeForHeight(const FVector2D ReferenceHeight, const FVector2D StartTime, const float MantlingHeight) const
{
	return FMath::GetMappedRangeValueClamped(ReferenceHeight, StartTime, MantlingHeight);
}

inline float UAlsxtMantlingSettings::GetPlayRateForHeight(const FVector2D ReferenceHeight, const FVector2D PlayRate, const float MantlingHeight) const
{
	return FMath::GetMappedRangeValueClamped(ReferenceHeight, PlayRate, MantlingHeight);
}

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtMantlingTraceSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0))
	FVector2D LedgeHeight{50.0f, 225.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm"))
	float ReachDistance{75.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm"))
	float TargetLocationOffset{15.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm"))
	float MaxDepth{20.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0))
	bool bDrawFailedTraces{false};
};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtGeneralMantlingSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	bool bAllowMantling{true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"))
	float TraceAngleThreshold{110.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"))
	float MaxReachAngle{50.0f};

	// If a dynamic object has a speed bigger than this value, then do not start mantling.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceUnits = "cm/s"))
	float TargetPrimitiveSpeedThreshold{10.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceUnits = "cm"))
	float MantlingHighHeightThreshold{125.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FAlsxtMantlingTraceSettings GroundedTrace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FAlsxtMantlingTraceSettings InAirTrace{{50.0f, 150.0f}, 70.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	TArray<TEnumAsByte<EObjectTypeQuery>> MantlingTraceObjectTypes;
};
