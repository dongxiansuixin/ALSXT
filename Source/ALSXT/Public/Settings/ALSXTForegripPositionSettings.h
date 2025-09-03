#pragma once

#include "Utility/AlsxtStructs.h"
#include "ALSXTForegripPositionSettings.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTForegripPositionSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FForegripPositions ForegripPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Debug {false};
};
