// MIT

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ALSXTAssetManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class ALSXT_API UALSXTAssetManagerBase : public UAssetManager
{
	GENERATED_BODY()
	
protected:
	virtual void StartInitialLoading() override;
	
	
};
