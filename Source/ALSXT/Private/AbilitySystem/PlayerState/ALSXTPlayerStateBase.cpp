// MIT


#include "AbilitySystem/PlayerState/ALSXTPlayerStateBase.h"


AALSXTPlayerStateBase::AALSXTPlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UALSXTAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	SetNetUpdateFrequency(100.0f);
}

