#pragma once

#include "AlsxtSlidingState.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtSlidingState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage{ nullptr };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	float TargetYawAngle{ 0.0f };
};

