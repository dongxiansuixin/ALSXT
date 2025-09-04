#pragma once

#include "Animation/AnimMontage.h"
#include "AlsxtFootstepEffectSettings.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtGeneralFootstepEffectSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableFootstepEffects { true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableEquipmentSounds{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableOverlayObjectSounds{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableVertexPaintTrace { true };

};
