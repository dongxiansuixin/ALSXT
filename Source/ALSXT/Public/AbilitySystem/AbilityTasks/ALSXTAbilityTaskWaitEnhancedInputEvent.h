// MIT

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "ALSXTAbilityTaskWaitEnhancedInputEvent.generated.h"

class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnhancedInputEventDelegate, FInputActionValue, Value);

UCLASS()
class ALSXT_API UALSXTAbilityTaskWaitEnhancedInputEvent : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable)
	FEnhancedInputEventDelegate InputEventReceived;
	
	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"), Category = "Ability Tasks")
	static UALSXTAbilityTaskWaitEnhancedInputEvent* WaitEnhancedInputEvent(UGameplayAbility* OwningAbility, const FName TaskInstanceName, UInputAction* InputAction, const ETriggerEvent TriggerEventType, bool bShouldOnlyTriggerOnce = true);

private:

	TWeakObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;
	
	TWeakObjectPtr<UInputAction> InputAction = nullptr;
	
	ETriggerEvent EventType;
	
	bool bTriggerOnce;

	bool bHasBeenTriggered = false;

	virtual void Activate() override;

	void EventReceived(const FInputActionValue& Value);

	virtual void OnDestroy(const bool bInOwnerFinished) override;
	
	
};
