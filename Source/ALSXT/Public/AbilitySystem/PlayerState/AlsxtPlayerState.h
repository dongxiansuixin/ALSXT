// MIT

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerState.h"
#include "../AbilitySystemComponent/AlsxtAbilitySystemComponent.h"
#include "AbilitySystem/Data/AlsxtAbilitySystemData.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "ALSXTCharacter.h"
#include "AlsxtPlayerState.generated.h"

class UALSXTCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class ALSXT_API AAlsxtPlayerState : public AModularPlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAlsxtPlayerState();

	UFUNCTION(BlueprintPure, Category = "MovementComponent")
	UALSXTCharacterMovementComponent* GetALSXTCharacterMovementComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{ return AbilitySystemComponent; }
	virtual UAlsxtAbilitySystemComponent* GetALSXTAbilitySystemComponent() const
	{ return AbilitySystemComponent; }

	void InitializeAbilitySystem();

	// This event is fired after Ability System Component initialization is finished.
	UFUNCTION(BlueprintNativeEvent)
	void PostInitializeAbilitySystem();

	UFUNCTION(BlueprintPure)
	const FAbilitySystemInitializationData& GetAbilitySystemInitializationData() const
	{
		return AbilitySystemInitializationData;
	}

protected:
	// Data used to initialize the Ability System Component. (Can be found in "AbilitySystemData.h")
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability System", Meta = (ShowOnlyInnerProperties))
	FAbilitySystemInitializationData AbilitySystemInitializationData;
	
	UAlsxtAbilitySystemComponent* AbilitySystemComponent;
	
	void MovementSpeedMultiplierChanged(const FOnAttributeChangeData& OnAttributeChangeData) const;	
	
};
