// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#include "AlsxtCharacterNPC.h"
#include "AbilitySystem/AbilitySystemComponent/AlsxtAbilitySystemComponent.h"

/**
* @file AlsxtCharacterNPC.cpp
* @brief Base AI ALSXT Character class. AI do not have Player States so we implement everything directly on the Avatar.
*/

void AAlsxtCharacterNPC::BeginPlay()
{
	Super::BeginPlay();
	 
	// Provide this character as owner and avatar
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AAlsxtCharacterNPC::InitializeAbilitySystem()
{
	if (!AbilitySystemComponent)
	{
		// Shouldn't happen, but if it is, return an error.
		return;
	}
	
	// Call the function on "Custom Ability System Component" to set up references and Init data. (Client)
	AbilitySystemComponent->InitializeAbilitySystemData(AbilitySystemInitializationData, this, this);

	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAlsxtMovementAttributeSet::GetMovementSpeedMultiplierAttribute()).AddUObject(this, &ThisClass::MovementSpeedMultiplierChanged);
	
	PostInitializeAbilitySystem();
}

void AAlsxtCharacterNPC::PostInitializeAbilitySystem_Implementation()
{
	if (!AbilitySystemComponent)
	{
		return;
	}
}