// Copyright (C) 2025 Uriel Ballinas, VOIDWARE Prohibited. All rights reserved.
// This software is licensed under the MIT License (LICENSE.md).

#pragma once

#include "CoreMinimal.h"
#include "AlsxtCharacter.h"
#include "AbilitySystem/PlayerState/AlsxtPlayerState.h"
#include "AlsxtCharacterPlayer.generated.h"

/**
* @file AlsxtCharacterPlayer.h
* @brief template class that contains all shared Logic and Data for Player Classes.
* AAlsxtCharacterPlayer depends on AAlsxtPlayerState and AAlsxtPlayerController to function.
* Create a Blueprint class based on this class, do not use the C++ class directly in the Editor
*/

UCLASS()
class ALSXT_API AAlsxtCharacterPlayer : public AAlsxtCharacter
{
	GENERATED_BODY()

public:
	TSoftObjectPtr<APlayerState> PlayerState;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAlsxtAbilitySystemComponent* GetAlsxtAbilitySystemComponent() const override;

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputMappingContext> InputMappingContextNew;
};
