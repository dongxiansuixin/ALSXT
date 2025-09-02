// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).


#include "AlsxtCharacterPlayer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AlsxtCharacterPlayer)

/**
* @file AlsxtCharacterPlayer.cpp
* @brief template class that contains all shared Logic and Data for Player Classes.
* AAlsxtCharacterPlayer depends on AAlsxtPlayerState and AAlsxtPlayerController to function.
* Create a Blueprint class based on this class, do not use the C++ class directly in the Editor
*/

void AAlsxtCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// Set a Soft Object Pointer to the Player State
	if (const APlayerController* CurrentPlayerController = Cast<APlayerController>(GetController()))
	{
		if (CurrentPlayerController->PlayerState)
		{
			PlayerState = CurrentPlayerController->PlayerState;
		}
	}
	
}

UAbilitySystemComponent* AAlsxtCharacterPlayer::GetAbilitySystemComponent() const
{
	if (IAlsxtAbilitySystemInterface* AlsxtAbilitySystemInterface = Cast<IAlsxtAbilitySystemInterface>(PlayerState.Get()))
	{
		return AlsxtAbilitySystemInterface->GetAbilitySystemComponent();
	}
	return nullptr;
}

UAlsxtAbilitySystemComponent* AAlsxtCharacterPlayer::GetAlsxtAbilitySystemComponent() const
{
	if (IAlsxtAbilitySystemInterface* AlsxtAbilitySystemInterface = Cast<IAlsxtAbilitySystemInterface>(PlayerState.Get()))
	{
		return AlsxtAbilitySystemInterface->GetAlsxtAbilitySystemComponent();
	}
	return nullptr;
}

