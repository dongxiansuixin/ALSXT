// MIT


#include "Components/Mesh/AlsxtViewModelStaticMeshComponent.h"
#include "AlsxtBlueprintFunctionLibrary.h"
#include "Interfaces/ALSXTControllerRenderInterface.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"

UAlsxtViewModelStaticMeshComponent::UAlsxtViewModelStaticMeshComponent()
{
}

void UAlsxtViewModelStaticMeshComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = GetWorld()->GetFirstPlayerController();
}

FMatrix UAlsxtViewModelStaticMeshComponent::GetRenderMatrix() const
{
	FMatrix Matrix = Super::GetRenderMatrix();
	
	if (!PlayerController.IsValid() || !PlayerController->GetPawn())
	{
		return Matrix;
	}

	if (!PlayerController->GetClass()->ImplementsInterface(UALSXTControllerRenderInterface::StaticClass()))
	{
		return Matrix;
	}

	APlayerController* PlayerControllerObject = PlayerController.Get();
	if (!IALSXTControllerRenderInterface::Execute_IsSeparateFirstPersonFOVEnabled(PlayerControllerObject) || !IALSXTControllerRenderInterface::Execute_IsViewModelOnStaticMeshEnabled(PlayerControllerObject))
	{
		return Matrix;
	}

	if (GetOwner())
	{
		AActor* OwningActor = GetOwner();
		for (uint8 i = 0; i < MaxOwnerAttempts; ++i)
		{
			if (APawn* OwningPawn = Cast<APawn>(OwningActor))
			{
				OwningActor = OwningPawn;
				break;
			}

			if (OwningActor)
			{
				OwningActor = OwningActor->GetOwner();
			}
			else
			{
				return Matrix;
			}
		}
		if (PlayerController->GetPawn() != OwningActor)
		{
			return Matrix;
		}
	}

	UAlsxtBlueprintFunctionLibrary::GetAdjustedRenderMatrix(this, PlayerController.Get(), DesiredFOV, Matrix);
	return Matrix;
}
