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
	// AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Gameplay.Ability.Sprint")));
	SetAssetTags(AssetTags);
	BaseStaminaCostPerSecond = 0.05f;
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
	
	FGameplayEffectContextHandle SprintGameplayEffectContextHandle = ActorInfo->AbilitySystemComponent.Get()->MakeEffectContext();
	SprintGameplayEffectContextHandle.SetAbility(this);

	// Apply stamina drain effect
	if (StaminaCostEffect)
	{
		// FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(Handle, ActorInfo, ActivationInfo, StaminaCostEffect, GetAbilityLevel());
		// FGameplayEffectSpecHandle SpecHandle2 = ActorInfo->AbilitySystemComponent.Get()->MakeOutgoingSpec(StaminaCostEffect,1, SprintGameplayEffectContextHandle);
		// FActiveGameplayEffectHandle ActiveGameplayEffectHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);

		FGameplayEffectContextHandle EffectContext = ActorInfo->AbilitySystemComponent.Get()->MakeEffectContext();
		// EffectContext.SetAbility(this);
		// FActiveGameplayEffectHandle ActiveGEHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
		// ActiveStaminaDrainEffectHandle = ActorInfo->AbilitySystemComponent.Get()->ApplyGameplayEffectToSelf(StaminaCostEffect.GetDefaultObject(), GetAbilityLevel(), EffectContext);

		// if (SpecHandle.IsValid())
		// {
		// 	// Set a fixed magnitude
		// 	SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(TEXT("Data.Magnitude.Sprint")), 50.0f);
		// 	ActiveStaminaDrainEffectHandle = ActorInfo->AbilitySystemComponent.Get()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		// }

		if (EffectContext.IsValid())
		{
			// ActiveStaminaDrainEffectHandle = ActorInfo->AbilitySystemComponent.Get()->ApplyGameplayEffectToSelf(StaminaCostEffect.GetDefaultObject(), GetAbilityLevel(), EffectContext);
		}
		
		
	}

	// ActorInfo->AbilitySystemComponent.Get()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
	// Apply stamina drain effect
	// if (StaminaCostEffect)
	// {
	// 	FGameplayEffectContextHandle EffectContext = ActorInfo->AbilitySystemComponent.Get()->MakeEffectContext();
	// 	// FActiveGameplayEffectHandle ActiveGEHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	// 	ActiveStaminaDrainEffectHandle = ActorInfo->AbilitySystemComponent.Get()->ApplyGameplayEffectToSelf(StaminaCostEffect.GetDefaultObject(), GetAbilityLevel(), EffectContext);
	// }

	AAlsxtCharacter* Character = Cast<AAlsxtCharacter>(ActorInfo->AvatarActor.Get());
	if (Character->CanSprint())
	{
		Character->SetDesiredGait(AlsGaitTags::Sprinting);
	}

	// Apply initial stamina cost and set up timer for continuous drain
	// GetWorld()->GetTimerManager().SetTimer(StaminaDrainTimerHandle, this, &UAlsxtGameplayAbilitySprint::ApplyStaminaCost, 0.2f, true);
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

	if (StaminaDrainTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaDrainTimerHandle);
	}

	
	if (HasAuthority(&ActivationInfo) && ActiveStaminaDrainEffectHandle.IsValid())
	{
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveStaminaDrainEffectHandle);
	}
	

	AAlsxtCharacter* Character = Cast<AAlsxtCharacter>(ActorInfo->AvatarActor.Get());
	Character->SetDesiredGait(AlsGaitTags::Running);

	// Apply stamina drain effect
	if (StaminaRegenEffect)
	{
		FGameplayEffectContextHandle EffectContext = ActorInfo->AbilitySystemComponent.Get()->MakeEffectContext();
		FGameplayEffectSpecHandle StaminaRegenSpecHandle = ActorInfo->AbilitySystemComponent.Get()->MakeOutgoingSpec(StaminaRegenEffect, GetAbilityLevel(), EffectContext);
		FGameplayEffectContextHandle StaminaRegenEffectContext = ActorInfo->AbilitySystemComponent.Get()->MakeEffectContext();
		StaminaRegenSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("StaminaCost.Infinite.Sprint")), -BaseStaminaCostPerSecond);
		// ActiveStaminaRegenEffectHandle = ActorInfo->AbilitySystemComponent.Get()->ApplyGameplayEffectToSelf(StaminaRegenEffect.GetDefaultObject(), 1.0f, EffectContext);
		ActiveStaminaRegenEffectHandle = ActorInfo->AbilitySystemComponent.Get()->ApplyGameplayEffectSpecToSelf(*StaminaRegenSpecHandle.Data.Get());
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UAlsxtGameplayAbilitySprint::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (!IsValid(ASC))
	{
		return false;
	}
	
	const UAlsxtStaminaAttributeSet* MyAttributeSet = ASC->GetSet<UAlsxtStaminaAttributeSet>();
	
	if (!IsValid(MyAttributeSet))
	{
		// Optionally, provide a reason why activation failed for debugging.
		// You can use a tag, for example: FGameplayTag::RequestGameplayTag(TEXT("Ability.Cost.MissingAttributeSet"));
		return false;
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UAlsxtGameplayAbilitySprint::ApplyStaminaCost()
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(StaminaCostEffect, GetAbilityLevel(), EffectContext);
		if (SpecHandle.IsValid() && SpecHandle.Data.IsValid())
		{
			// SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(TEXT("StaminaCost.Infinite.Sprint")), 50.0f);
			SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("StaminaCost.Infinite.Sprint")), -BaseStaminaCostPerSecond);
			ASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), ASC);
			// ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

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
