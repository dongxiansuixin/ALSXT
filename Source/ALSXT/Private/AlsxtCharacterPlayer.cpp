// MIT


#include "AlsxtCharacterPlayer.h"


bool AAlsxtCharacterPlayer::VerifyPlayerControllerDependency() const
{
	// Get the owning Player Controller
	APlayerController* CurrentPlayerController = Cast<APlayerController>(GetController());

	if (CurrentPlayerController)
	{
		// Attempt to cast to your custom Player State class
		AALSXTPlayerController* ALSXTPlayerControllerDependency = Cast<AALSXTPlayerController>(CurrentPlayerController);

		// If the cast is successful, it means your custom Player Controller class is in use
		return ALSXTPlayerControllerDependency != nullptr;			
	}

	return false; // No Player Controller found
}

bool AAlsxtCharacterPlayer::VerifyPlayerStateDependency() const
{
	// Get the owning Player Controller
	APlayerController* CurrentPlayerController = Cast<APlayerController>(GetController());

	if (CurrentPlayerController)
	{
		// Get the Player State from the Player Controller
		APlayerState* CurrentPlayerState = CurrentPlayerController->PlayerState;

		// Attempt to cast to your custom Player State class
		AAlsxtPlayerState* ALSXTPlayerStateDependency = Cast<AAlsxtPlayerState>(CurrentPlayerState);

		// If the cast is successful, it means your custom Player State class is in use
		return ALSXTPlayerStateDependency != nullptr;
	}

	return false; // No Player Controller or Player State found
}

