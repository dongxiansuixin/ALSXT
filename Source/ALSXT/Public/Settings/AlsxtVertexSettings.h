#pragma once

#include "Engine/DataAsset.h"
#include "Utility/AlsxtVertexStructs.h"
#include "AlsxtVertexSettings.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ALSXT_API UAlsxtVertexColorPhysicalMaterialMap : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vertex Utilities")
	FAlsxtVertexColorToPhysicalMaterialMap VertexColorPhysicalMaterialMap;
};
