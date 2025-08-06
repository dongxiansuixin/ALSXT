// MIT


#include "AbilitySystem/AttributeSets/ALSXTLevelAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/AbilitySystemComponent/ALSXTAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UALSXTLevelAttributeSet::UALSXTLevelAttributeSet()
{
	InitMaximumLevel(0.f);
	InitCurrentLevel(0.f);
}

void UALSXTLevelAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);

	if (Attribute != GetCurrentLevelAttribute())
	{
		return;
	}

	if (UALSXTAbilitySystemComponent* const ASC = Cast<UALSXTAbilitySystemComponent>(GetOwningAbilitySystemComponent()))
	{
		ASC->ChangeLevel(NewValue);
	}
}

void UALSXTLevelAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams Params{};
	Params.bIsPushBased = true;
	Params.Condition = COND_None;

	// Replicated to all
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTLevelAttributeSet, CurrentLevel, Params);
	
	// Only Owner
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(UALSXTLevelAttributeSet, MaximumLevel, Params);
}

void UALSXTLevelAttributeSet::OnRep_CurrentLevel(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTLevelAttributeSet, CurrentLevel, OldValue);
}

void UALSXTLevelAttributeSet::OnRep_MaximumLevel(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UALSXTLevelAttributeSet, MaximumLevel, OldValue);
}