#pragma once

#include "Engine/DataAsset.h"
#include "Utility/AlsxtVertexStructs.h"
#include "ALSXTVertexSettings.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ALSXT_API UALSXTVertexColorPhysicalMaterialMap : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vertex Utilities")
	FALSXTVertexColorToPhysicalMaterialMap VertexColorPhysicalMaterialMap;
};
