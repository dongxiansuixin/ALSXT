// MIT

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbilities/AlsxtGameplayAbilityBase.h"
#include "AlsxtGameplayAbilitySprint.generated.h"

struct FEventData;
/**
 * 
 */
UCLASS()
class ALSXT_API UAlsxtGameplayAbilitySprint : public UAlsxtGameplayAbilityBase
{
	GENERATED_BODY()
	
public:
	UAlsxtGameplayAbilitySprint();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
	float BaseStaminaCostPerSecond; // Unique cost for sprint

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	TSubclassOf<UGameplayEffect> StaminaCostEffect;

	UPROPERTY()
	FTimerHandle StaminaDrainTimerHandle;

	FActiveGameplayEffectHandle ActiveStaminaDrainEffectHandle;
	
	void ApplyStaminaCost();
};
