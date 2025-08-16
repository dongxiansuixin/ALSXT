// MIT


#include "AbilitySystem/AssetManager/ALSXTAssetManagerBase.h"
#include "AbilitySystemGlobals.h"


void UALSXTAssetManagerBase::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();

	UE_LOG(LogTemp, Display, TEXT("Loading ALSXT Asset Manager"));
}



