#pragma once
#include "Settings/ALSXTImpactReactionSettings.h"
#include "Utility/AlsxtCollisionGameplayTags.h"
#include "ALSXTImpactReactionState.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTImpactReactionState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	FALSXTImpactReactionParameters ImpactReactionParameters;
};

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTPhysicalAnimationState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	FGameplayTag Mode {ALSXTPhysicalAnimationModeTags::None };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	FName ProfileName {"CharacterMesh"};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TArray<FName> AffectedBonesBelow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float Alpha { 0.0f };
};