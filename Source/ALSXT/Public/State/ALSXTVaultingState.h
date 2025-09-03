#pragma once

#include "Engine/EngineTypes.h"
#include "Utility/AlsxtStructs.h"
#include "Settings/ALSXTVaultingSettings.h"
#include "ALSXTVaultingState.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTVaultingState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FALSXTVaultingParameters VaultingParameters;
};

