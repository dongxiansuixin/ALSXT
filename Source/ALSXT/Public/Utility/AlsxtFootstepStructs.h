#pragma once

#include "NativeGameplayTags.h"
#include "AlsxtFootstepStructs.generated.h"

enum EAlsFootstepSoundType : int;


USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtFootstepEffectCriteria
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TSoftClassPtr<UPhysicalMaterial> FootSurface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TSoftClassPtr<UPhysicalMaterial> GroundSurface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	EAlsFootstepSoundType StepType;

	bool operator==(const FAlsxtFootstepEffectCriteria& other) const
	{
		return (other.FootSurface == FootSurface) && (other.GroundSurface == GroundSurface) && (other.StepType == StepType);
	}
};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtFootstepEffectVertexCriteria
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FAlsxtFootstepEffectCriteria FootstepTraceResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TSoftClassPtr<UPhysicalMaterial> VertexSurface;	

	bool operator==(const FAlsxtFootstepEffectVertexCriteria& other) const
	{
		return (other.FootstepTraceResult == FootstepTraceResult) && (other.VertexSurface == VertexSurface);
	}
};
