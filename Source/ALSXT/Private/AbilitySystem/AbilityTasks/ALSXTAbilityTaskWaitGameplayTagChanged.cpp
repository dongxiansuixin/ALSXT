// MIT


#include "AbilitySystem/AbilityTasks/ALSXTAbilityTaskWaitGameplayTagChanged.h"
#include "AbilitySystemComponent.h"

void UALSXTAbilityTaskWaitGameplayTagChanged::Activate()
{
	UAbilitySystemComponent* const ASC = GetTargetASC();
	if (ASC && ShouldBroadcastAbilityTaskDelegates() && bTriggerAtActivation)
	{
		if (ASC->HasMatchingGameplayTag(Tag))
		{
			const int32 TagCount = ASC->GetGameplayTagCount(Tag);
			Added.Broadcast(TagCount, TagCount);
		}
		else
		{
			Removed.Broadcast(0, 0);
		}
		
		if(OnlyTriggerOnce)
		{
			EndTask();
			return;
		}
	}

	if (!ASC)
	{
		EndTask();
		return;
	}

	if (ASC)
	{
		DelegateHandle = ASC->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::AnyCountChange).AddUObject(this, &UAbilityTask_WaitGameplayTag::GameplayTagCallback);
		RegisteredCallback = true;
	}
}
	
UALSXTAbilityTaskWaitGameplayTagChanged* UALSXTAbilityTaskWaitGameplayTagChanged::WaitGameplayTagChanged(UGameplayAbility* OwningAbility, FGameplayTag Tag, AActor* InOptionalExternalTarget, bool bOnlyTriggerOnce /* = false */, bool bTriggerAtActivation /* = false */)
{
	UALSXTAbilityTaskWaitGameplayTagChanged* MyObj = NewAbilityTask<UALSXTAbilityTaskWaitGameplayTagChanged>(OwningAbility);
	MyObj->Tag = Tag;
	MyObj->SetExternalTarget(InOptionalExternalTarget);
	MyObj->OnlyTriggerOnce = bOnlyTriggerOnce;
	MyObj->bTriggerAtActivation = bTriggerAtActivation;

	return MyObj;
}

void UALSXTAbilityTaskWaitGameplayTagChanged::GameplayTagCallback(const FGameplayTag InTag, int32 NewCount)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (NewCount > 0)
		{
			Added.Broadcast(NewCount, NewCount - PreviousCount);
		}
		else
		{
			Removed.Broadcast(NewCount, NewCount - PreviousCount);
		}
	}

	PreviousCount = NewCount;

	if (OnlyTriggerOnce)
	{
		EndTask();
	}
}


