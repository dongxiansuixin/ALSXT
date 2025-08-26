#pragma once

#include "NativeGameplayTags.h"
#include "ALSXTFootstepStructs.generated.h"

enum EAlsFootstepSoundType : int;


USTRUCT(BlueprintType)
struct ALSXT_API FALSXTFootstepEffectCriteria
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TSoftClassPtr<UPhysicalMaterial> FootSurface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TSoftClassPtr<UPhysicalMaterial> GroundSurface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	EAlsFootstepSoundType StepType;

	bool operator==(const FALSXTFootstepEffectCriteria& other) const
	{
		return (other.FootSurface == FootSurface) && (other.GroundSurface == GroundSurface) && (other.StepType == StepType);
	}
};

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTFootstepEffectVertexCriteria
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FALSXTFootstepEffectCriteria FootstepTraceResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TSoftClassPtr<UPhysicalMaterial> VertexSurface;	

	bool operator==(const FALSXTFootstepEffectVertexCriteria& other) const
	{
		return (other.FootstepTraceResult == FootstepTraceResult) && (other.VertexSurface == VertexSurface);
	}
};
