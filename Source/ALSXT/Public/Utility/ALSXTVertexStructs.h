#pragma once

#include "Utility/ALSXTVertexEnums.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Chaos/ChaosEngineInterface.h"
#include "ALSXTVertexStructs.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTVertexColorToPhysicalMaterialMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TMap<EVertexColorChannel, UPhysicalMaterial*> VertexColorPhysicalMaterialMap;
};