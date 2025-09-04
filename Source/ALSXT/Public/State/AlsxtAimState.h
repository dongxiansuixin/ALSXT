#pragma once

#include "GameplayTagContainer.h"
#include "AlsxtAimState.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtAimState
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		bool CanAim {true};

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
		FTransform CurrentHeadTargetTransform;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
		FTransform CurrentHeadTargetTransformOffset;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
		FTransform CurrentCameraTargetRelativeTransform;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
		FTransform CurrentCameraTargetTransform;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Origin")
		FVector CurrentTarget{ EForceInit::ForceInit };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		float CurrentFOV {90.0f};
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
		FRotator ControlRotation { EForceInit::ForceInit };

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayTag WeaponReadyPosition{ FGameplayTag::EmptyTag };

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayTag FirearmStance{ FGameplayTag::EmptyTag };

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector TargetPoint{ EForceInit::ForceInit };
};

