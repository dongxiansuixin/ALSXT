#pragma once

#include "Utility/AlsxtVertexEnums.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Chaos/ChaosEngineInterface.h"
#include "AlsxtVertexStructs.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtVertexColorToPhysicalMaterialMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TMap<EVertexColorChannel, UPhysicalMaterial*> VertexColorPhysicalMaterialMap;
};