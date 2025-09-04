#pragma once

#include "NativeGameplayTags.h"
#include "Animation/AnimMontage.h"
#include "Engine/EngineTypes.h"
#include "ALSXTAnimationStructs.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtPoseSingleFrame
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TObjectPtr<UAnimSequenceBase> Pose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float ExplicitTime {0.0f};

	bool operator==(const FAlsxtPoseSingleFrame& other) const
	{
		return (other.Pose == Pose) && (other.ExplicitTime == ExplicitTime);
	}

};