// MIT

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerState.h"
#include "../AbilitySystemComponent/ALSXTAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "ALSXTPlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class ALSXT_API AALSXTPlayerStateBase : public AModularPlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AALSXTPlayerStateBase();

protected:
	UALSXTAbilitySystemComponent* AbilitySystemComponent;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const
	{ return AbilitySystemComponent; }
	
};
