// MIT

#pragma once

#include "CoreMinimal.h"
#include "ALSXTCharacter.h"
#include "ALSXTPlayerController.h"
#include "AbilitySystem/PlayerState/AlsxtPlayerState.h"
#include "AlsxtCharacterPlayer.generated.h"

// AALSXTCharacterPlayer is a template class that contains all shared Logic and Data for Player Classes.
// AALSXTCharacterPlayer depends on AALSXTPlayerState and AALSXTPlayerController to function.
// Create a Blueprint class based on this class, do not use the C++ class directly in the Editor
UCLASS()
class ALSXT_API AAlsxtCharacterPlayer : public AALSXTCharacter
{
	GENERATED_BODY()
	
public:
	// Function to check if a specific Player Controller class is being used
	bool VerifyPlayerControllerDependency() const;

	// Function to check if a specific Player State class is being used
	bool VerifyPlayerStateDependency() const;
	
	
};
