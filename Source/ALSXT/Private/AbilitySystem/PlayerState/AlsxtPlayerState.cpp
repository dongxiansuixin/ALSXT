// MIT


#include "AbilitySystem/PlayerState/AlsxtPlayerState.h"

#include "ALSXTCharacter.h"
#include "AbilitySystem/AttributeSets/AlsxtMovementAttributeSet.h"


AAlsxtPlayerState::AAlsxtPlayerState()
{
	// If the NetUpdateFrequency is too low, there will be a delay on Ability activation / Effect application on the client.
	SetNetUpdateFrequency(100.0f);

	// Create the Ability System Component sub-object.
	AbilitySystemComponent = CreateDefaultSubobject<UAlsxtAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Set Replication Mode to Mixed for Players.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UALSXTCharacterMovementComponent* AAlsxtPlayerState::GetALSXTCharacterMovementComponent() const
{
	if (Cast<AALSXTCharacter>(GetPawn()))
	{
		return Cast<UALSXTCharacterMovementComponent>(Cast<AALSXTCharacter>(GetPawn())->GetCharacterMovement());
	}
	return nullptr;
}

void AAlsxtPlayerState::InitializeAbilitySystem()
{
	if (!AbilitySystemComponent)
	{
		// Shouldn't happen, but if it is, return an error.
		return;
	}
	
	// Call the function on "Custom Ability System Component" to set up references and Init data. (Client)
	AbilitySystemComponent->InitializeAbilitySystemData(AbilitySystemInitializationData, this, this);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAlsxtMovementAttributeSet::GetMovementSpeedMultiplierAttribute()).AddUObject(this, &ThisClass::MovementSpeedMultiplierChanged);
	
	PostInitializeAbilitySystem();
}

void AAlsxtPlayerState::PostInitializeAbilitySystem_Implementation()
{
	if (!AbilitySystemComponent)
	{
		return;
	}
}

void AAlsxtPlayerState::MovementSpeedMultiplierChanged(const FOnAttributeChangeData& OnAttributeChangeData) const
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), OnAttributeChangeData.NewValue);
	GetALSXTCharacterMovementComponent()->SetMovementSpeedMultiplier(OnAttributeChangeData.NewValue);
}