// MIT

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ALSXTAbilityTaskOnTickEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTickEventDelegate, float, DeltaTime);

UCLASS()
class ALSXT_API UALSXTAbilityTaskOnTickEvent : public UAbilityTask
{
	GENERATED_BODY()
	
public:

	UALSXTAbilityTaskOnTickEvent();
	
	UPROPERTY(BlueprintAssignable)
	FTickEventDelegate TickEventReceived;
	
	UFUNCTION(BlueprintCallable, Meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "True"), Category = "Ability Tasks")
	static UALSXTAbilityTaskOnTickEvent* OnTickEvent(UGameplayAbility* OwningAbility, const FName TaskInstanceName);

protected:

	virtual void TickTask(const float DeltaTime) override;
	
	void EventReceived(const float DeltaTime) const;

	virtual void OnDestroy(const bool bInOwnerFinished) override;
	
	
};
