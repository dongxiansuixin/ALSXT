// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#pragma once

#include "CoreMinimal.h"
#include "ALSXTCharacter.h"
#include "AbilitySystem/PlayerState/AlsxtPlayerState.h"
#include "AlsxtCharacterPlayer.generated.h"

// class AlsxtPlayerController;

// AAlsxtCharacterPlayer is a template class that contains all shared Logic and Data for Player Classes.
// AAlsxtCharacterPlayer depends on AAlsxtPlayerState and AAlsxtPlayerController to function.
// Create a Blueprint class based on this class, do not use the C++ class directly in the Editor
UCLASS()
class ALSXT_API AAlsxtCharacterPlayer : public AALSXTCharacter
{
	GENERATED_BODY()

public:
	TSoftObjectPtr<APlayerState> PlayerState;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAlsxtAbilitySystemComponent* GetAlsxtAbilitySystemComponent() const override;

	virtual void BeginPlay() override;
	
};
