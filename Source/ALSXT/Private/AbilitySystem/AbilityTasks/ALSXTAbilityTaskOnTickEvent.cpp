// MIT


#include "AbilitySystem/AbilityTasks/ALSXTAbilityTaskOnTickEvent.h"

UALSXTAbilityTaskOnTickEvent::UALSXTAbilityTaskOnTickEvent()
{
	bTickingTask = true;
	bSimulatedTask = true;
}

UALSXTAbilityTaskOnTickEvent* UALSXTAbilityTaskOnTickEvent::OnTickEvent(UGameplayAbility* OwningAbility, const FName TaskInstanceName)
{
	return NewAbilityTask<UALSXTAbilityTaskOnTickEvent>(OwningAbility, TaskInstanceName);
}

void UALSXTAbilityTaskOnTickEvent::TickTask(const float DeltaTime)
{
	Super::TickTask(DeltaTime);

	EventReceived(DeltaTime);
}

void UALSXTAbilityTaskOnTickEvent::EventReceived(const float DeltaTime) const
{
	if (TickEventReceived.IsBound())
	{
		TickEventReceived.Broadcast(DeltaTime);
	}
}

void UALSXTAbilityTaskOnTickEvent::OnDestroy(const bool bInOwnerFinished)
{
	bTickingTask = false;
	
	Super::OnDestroy(bInOwnerFinished);
}


