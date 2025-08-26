// MIT

#include "AbilitySystem/GameplayAbilities/ALSXTGameplayAbilityClientToServer.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"

void UALSXTGameplayAbilityClientToServer::ActivateLocalPlayerAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	K2_ActivateLocalPlayerAbility();
}

void UALSXTGameplayAbilityClientToServer::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!bUseClientServerFeature)
	{
		return;
	}
	
	if (GetActorInfo().IsLocallyControlled())
	{
		ActivateLocalPlayerAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, TriggerEventData);
		return;
	}

	if (GetActorInfo().IsNetAuthority())
	{
		ActivateServerAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, TriggerEventData);
	}
}

void UALSXTGameplayAbilityClientToServer::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	EndAbilityCleanup(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UALSXTGameplayAbilityClientToServer::ActivateAbilityWithTargetData_Implementation(
	const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag ApplicationTag)
{
}

void UALSXTGameplayAbilityClientToServer::NotifyTargetDataReady(const FGameplayAbilityTargetDataHandle& InData, FGameplayTag ApplicationTag)
{
	if (!bUseClientServerFeature)
	{
		return;
	}
	
	UAbilitySystemComponent* const ASC = CurrentActorInfo->AbilitySystemComponent.Get();
	check(ASC);

	if (!ASC->FindAbilitySpecFromHandle(CurrentSpecHandle))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);  // do not replicate
		return;
	}

	// true if we need to replicate this target data to the server
	const bool bShouldNotifyServer = CurrentActorInfo->IsLocallyControlled() && !CurrentActorInfo->IsNetAuthority();

	// Start a scoped prediction window
	FScopedPredictionWindow	ScopedPrediction(ASC);

	// Lyra does this memcopy operation; const cast paranoia is real. We'll keep it.
	// Take ownership of the target data to make sure no callbacks into game code invalidate it out from under us
	const FGameplayAbilityTargetDataHandle LocalTargetDataHandle(MoveTemp(const_cast<FGameplayAbilityTargetDataHandle&>(InData)));

	// if this isn't the local player on the server, then notify the server
	if (bShouldNotifyServer)
	{
		ASC->CallServerSetReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey(), LocalTargetDataHandle, ApplicationTag, ASC->ScopedPredictionKey);
	}

	// Execute the ability we've now successfully committed
	ActivateAbilityWithTargetData(LocalTargetDataHandle, ApplicationTag);

	// We've processed the data, clear it from the RPC buffer
	ASC->ConsumeClientReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey());
}

void UALSXTGameplayAbilityClientToServer::ActivateServerAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!bUseClientServerFeature)
	{
		return;
	}
	
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	check(ASC);

	// plug into AbilitySystemComponent to receive Target Data from client
	NotifyTargetDataReadyDelegateHandle = ASC->AbilityTargetDataSetDelegate(Handle, ActivationInfo.GetActivationPredictionKey()).AddUObject(this, &ThisClass::NotifyTargetDataReady);
}

void UALSXTGameplayAbilityClientToServer::EndAbilityCleanup(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!bUseClientServerFeature)
	{
		return;
	}
	
	UAbilitySystemComponent* const ASC = CurrentActorInfo->AbilitySystemComponent.Get();
	check(ASC);

	// Clean up
	if (!ASC)
	{
		return;
	}
	ASC->AbilityTargetDataSetDelegate(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey()).Remove(NotifyTargetDataReadyDelegateHandle);
	ASC->ConsumeClientReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey());
}

FGameplayAbilityTargetDataHandle UALSXTGameplayAbilityClientToServer::MakeAbilityTargetLocationHandle(const FGameplayAbilityTargetingLocationInfo& SourceLocation, const FGameplayAbilityTargetingLocationInfo& TargetLocation)
{
	// Construct TargetData
	FGameplayAbilityTargetData_LocationInfo* NewData = new FGameplayAbilityTargetData_LocationInfo();
	NewData->SourceLocation = SourceLocation;
	NewData->TargetLocation = TargetLocation;

	// Give it a handle and return
	FGameplayAbilityTargetDataHandle Handle{};
	Handle.Data.Add(TSharedPtr<FGameplayAbilityTargetData_LocationInfo>(NewData));
	return Handle;
}
