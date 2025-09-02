// MIT


#include "Notify/ALSXTAnimNotify_CharacterMovementSound.h"
#include "AlsCharacter.h"
#include "ALSXTAnimationInstance.h"
#include "ALSXTCharacter.h"
#include "Interfaces/AlsxtCharacterInterface.h"
#include "Interfaces/AlsxtCharacterSoundComponentInterface.h"

// ReSharper disable once CppUnusedIncludeDirective
#include UE_INLINE_GENERATED_CPP_BY_NAME(ALSXTAnimNotify_CharacterMovementSound)


FString UALSXTAnimNotify_CharacterMovementSound::GetNotifyName_Implementation() const
{
	return FString("ALSXT Character Movement Sound Notify");
}

void UALSXTAnimNotify_CharacterMovementSound::Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(Mesh, Animation, EventReference);

	if (!IsValid(Mesh))
	{
		return;
	}

	const auto* World{ Mesh->GetWorld() };

	if (World->WorldType != EWorldType::EditorPreview)
	{
		FGameplayTag WeightTag = IAlsxtCharacterInterface::Execute_GetWeightTag(Mesh->GetOwner());
		IAlsxtCharacterSoundComponentInterface::Execute_PlayCharacterMovementSound(Mesh->GetOwner(), EnableCharacterMovementAccentSound, EnableWeaponMovementSound, MovementType, WeightTag);
	}
}