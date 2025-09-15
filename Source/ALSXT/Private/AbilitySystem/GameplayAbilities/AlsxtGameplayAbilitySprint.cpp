// MIT


#include "AbilitySystem/GameplayAbilities/AlsxtGameplayAbilitySprint.h"
#include "AbilitySystem/AbilitySystemComponent/AlsxtAbilitySystemComponent.h"
#include "AlsxtCharacter.h"
#include "AlsxtCharacterMovementComponent.h"
#include "AbilitySystem/AttributeSets/AlsxtStaminaAttributeSet.h"
#include "GameplayEffect.h"

UAlsxtGameplayAbilitySprint::UAlsxtGameplayAbilitySprint()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	FGameplayTagContainer AssetTags = { };
	AssetTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Gameplay.Ability.Sprint")));
	SetAssetTags(AssetTags);
	BaseStaminaCostPerSecond = 5.0f;
}

void UAlsxtGameplayAbilitySprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// Apply stamina drain effect
	// if (StaminaCostEffect)
	// {
	// 	FGameplayEffectContextHandle EffectContext = ActorInfo->AbilitySystemComponent.Get()->MakeEffectContext();
	// 	ActiveStaminaDrainEffectHandle = ActorInfo->AbilitySystemComponent.Get()->ApplyGameplayEffectToSelf(StaminaCostEffect.GetDefaultObject(), 1.0f, EffectContext);
	// }

	AAlsxtCharacter* Character = Cast<AAlsxtCharacter>(ActorInfo->AvatarActor.Get());
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed *= 2.0f; // Example speed increase
	}

	// Apply initial stamina cost and set up timer for continuous drain
	GetWorld()->GetTimerManager().SetTimer(StaminaDrainTimerHandle, this, &UAlsxtGameplayAbilitySprint::ApplyStaminaCost, 1.0f, true);
}

void UAlsxtGameplayAbilitySprint::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}

	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UAlsxtGameplayAbilitySprint::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(StaminaDrainTimerHandle);

	AAlsxtCharacter* Character = Cast<AAlsxtCharacter>(ActorInfo->AvatarActor.Get());
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed /= 2.0f; // Reset speed
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UAlsxtGameplayAbilitySprint::ApplyStaminaCost()
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(StaminaCostEffect, 1.0f, EffectContext);
		if (SpecHandle.IsValid())
		{
			SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.StaminaCost")), -BaseStaminaCostPerSecond);
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

			// Check if stamina is below threshold to end ability
			if (const UAlsxtStaminaAttributeSet* StaminaSet = ASC->GetSet<UAlsxtStaminaAttributeSet>())
			{
				if (StaminaSet->GetCurrentStamina() <= 0.0f) // Or your defined threshold
				{
					EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
				}
			}
		}
	}
}
