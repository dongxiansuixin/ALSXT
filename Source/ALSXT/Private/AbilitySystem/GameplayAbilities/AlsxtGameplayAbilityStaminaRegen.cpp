// MIT


#include "AbilitySystem/GameplayAbilities/AlsxtGameplayAbilityStaminaRegen.h"
#include "AbilitySystem/AbilitySystemComponent/AlsxtAbilitySystemComponent.h"
#include "AlsxtCharacter.h"
#include "AlsxtCharacterMovementComponent.h"
#include "AbilitySystem/AttributeSets/AlsxtStaminaAttributeSet.h"
#include "GameplayEffect.h"
// #include "TimerManager.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"

UAlsxtGameplayAbilityStaminaRegen::UAlsxtGameplayAbilityStaminaRegen()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	FGameplayTagContainer AssetTags = { };
	AssetTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Gameplay.Ability.StaminaRegen")));
	// AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Gameplay.Ability.StaminaRegen")));
	SetAssetTags(AssetTags);
	BaseStaminaRegenPerSecond = 0.05f;
	StaminaRegenTag = FGameplayTag::RequestGameplayTag(FName("StaminaCost.Infinite.Sprint"));

	CancelAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Cooldown.StaminaRegen")));

	// Add a requirement: does NOT have the StaminaConsumptionActive tag
	BlockAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Consuming.Stamina")));
}

void UAlsxtGameplayAbilityStaminaRegen::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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

	if (StaminaRegenEffect)
	{
		// FTimerManager& TimerManager = ActorInfo->OwnerActor->GetWorldTimerManager();
		// TimerManager.SetTimer(DelayTimerHandle, this, &UAlsxtGameplayAbilityStaminaRegen::OnDelayFinished, DelayDuration, false);

		UAbilityTask_WaitDelay* WaitTask = UAbilityTask_WaitDelay::WaitDelay(this, DelayDuration);
		WaitTask->OnFinish.AddDynamic(this, &UAlsxtGameplayAbilityStaminaRegen::OnDelayFinished);
		WaitTask->Activate();

	}

	AAlsxtCharacter* Character = Cast<AAlsxtCharacter>(ActorInfo->AvatarActor.Get());
	if (Character->CanSprint())
	{
		Character->SetDesiredGait(AlsGaitTags::Sprinting);
	}
}

void UAlsxtGameplayAbilityStaminaRegen::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}

	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UAlsxtGameplayAbilityStaminaRegen::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}

	// Remove the stamina drain Gameplay Effect
	if (HasAuthority(&ActivationInfo) && StaminaRegenEffectSpecHandle.IsValid())
	{
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(StaminaRegenEffect, ActorInfo->AbilitySystemComponent.Get(), -1);
	}

	
	// if (HasAuthority(&ActivationInfo) && ActiveStaminaDrainEffectHandle.IsValid())
	// {
	// 	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveStaminaDrainEffectHandle);
	// }

	// if (GetWorld()->GetTimerManager().IsTimerActive(DelayTimerHandle))
	// {
	// 	GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
	// }
	

	AAlsxtCharacter* Character = Cast<AAlsxtCharacter>(ActorInfo->AvatarActor.Get());
	Character->SetDesiredGait(AlsGaitTags::Running);
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UAlsxtGameplayAbilityStaminaRegen::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (!IsValid(ASC))
	{
		return false;
	}
	
	const UAlsxtStaminaAttributeSet* StaminaAttributeSet = ASC->GetSet<UAlsxtStaminaAttributeSet>();
	
	if (!IsValid(StaminaAttributeSet))
	{
		// Optionally, provide a reason why activation failed for debugging.
		// You can use a tag, for example: FGameplayTag::RequestGameplayTag(TEXT("Ability.Cost.MissingAttributeSet"));
		return false;
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UAlsxtGameplayAbilityStaminaRegen::OnDelayFinished()
{
	FGameplayEffectContextHandle EffectContext = GetActorInfo().AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddInstigator(GetActorInfo().AvatarActor.Get(), GetActorInfo().AvatarActor.Get());
	StaminaRegenEffectSpecHandle = GetActorInfo().AbilitySystemComponent->MakeOutgoingSpec(StaminaRegenEffect, 1.0f, EffectContext);
	StaminaRegenEffectSpecHandle.Data->SetSetByCallerMagnitude(StaminaRegenTag, -BaseStaminaRegenPerSecond);
        
	if (StaminaRegenEffectSpecHandle.IsValid())
	{
		GetActorInfo().AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*StaminaRegenEffectSpecHandle.Data.Get());
	}
}
