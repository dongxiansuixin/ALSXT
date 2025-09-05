#include "AbilitySystem/GameplayAbilities/AlsxtGameplayAbilityBreathing.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

UAlsxtGameplayAbilityBreathing::UAlsxtGameplayAbilityBreathing()
{
	// Set the ability to be passive and auto-activate.
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Gameplay.State.Dead")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Gameplay.Ability.Breathing")));
	// bServerRespectsRemoteActivation = false;
	bServerRespectsRemoteAbilityCancellation = false;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
}

void UAlsxtGameplayAbilityBreathing::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (ActorInfo->IsNetAuthority())
		{
			FGameplayEffectContextHandle EffectContext = ActorInfo->AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			// FGameplayEffectSpecHandle SpecHandle = ActorInfo->AbilitySystemComponent->MakeOutgoingGameplayEffectSpec(BreathingEffect, GetAbilityLevel(), EffectContext);
			FGameplayEffectSpecHandle SpecHandle = ActorInfo->AbilitySystemComponent->MakeOutgoingSpec(BreathingEffect, GetAbilityLevel(), EffectContext);

			if (SpecHandle.IsValid())
			{
				ActiveEffectHandle = ActorInfo->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

void UAlsxtGameplayAbilityBreathing::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (ActiveEffectHandle.IsValid())
	{
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandle);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
