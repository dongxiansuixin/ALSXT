// MIT


#include "Components/Character/ALSXTCharacterCustomizationComponent.h"
#include "Components/Mesh/AlsxtPaintableSkeletalMeshComponent.h"

// Sets default values for this component's properties
UALSXTCharacterCustomizationComponent::UALSXTCharacterCustomizationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UALSXTCharacterCustomizationComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UALSXTCharacterCustomizationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FALSXTCharacterVoiceParameters UALSXTCharacterCustomizationComponent::GetVoiceParameters()
{
	return VoiceParameters;
}

TArray<UAlsxtPaintableSkeletalMeshComponent*> UALSXTCharacterCustomizationComponent::GetAllComponents()
{
	TArray<UAlsxtPaintableSkeletalMeshComponent*> AllComponents;
	return AllComponents;
}

TArray<UAlsxtPaintableSkeletalMeshComponent*> UALSXTCharacterCustomizationComponent::GetHighlightableComponents()
{
	TArray<UAlsxtPaintableSkeletalMeshComponent*> AllComponents {GetAllComponents()};
	TArray<UAlsxtPaintableSkeletalMeshComponent*> HighlightableComponents;

	for (UAlsxtPaintableSkeletalMeshComponent* Component : AllComponents)
	{
		if (IsValid(Component))
		{
			HighlightableComponents.Add(Component);
		}
	}
	return HighlightableComponents;
}

