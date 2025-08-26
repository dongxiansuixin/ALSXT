// MIT

#pragma once

#include "CoreMinimal.h"
#include "ALSXTCharacter.h"
#include "AbilitySystem/Data/ALSXTAbilitySystemData.h"
#include "AbilitySystem/AbilitySystemComponent/ALSXTAbilitySystemComponent.h"
#include "UObject/ObjectPtr.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "ALSXTCharacterMovementComponent.h"
#include "GameplayEffectTypes.h"
#include "ALSXTCharacterNPC.generated.h"


// AALSXTCharacterNPC is a template class that contains all shared Logic and Data for NPC Classes.
// Create a Blueprint class based on this class, do not use the C++ class directly in the Editor
UCLASS()
class ALSXT_API AALSXTCharacterNPC : public AALSXTCharacter
{
	GENERATED_BODY()

};