#pragma once

#include "Settings/ALSXTClothingSettings.h"
#include "AlsxtClothingState.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtClothingState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FALSXTClothingParameters ClothingParameters;
};

