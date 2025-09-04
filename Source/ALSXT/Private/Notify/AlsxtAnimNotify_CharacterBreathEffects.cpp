// MIT


#include "Notify/AlsxtAnimNotify_CharacterBreathEffects.h"
#include "AlsCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "AlsxtAnimationInstance.h"
#include "AlsxtCharacter.h"
#include "Interfaces/AlsxtCharacterInterface.h"
#include "Interfaces/AlsxtCharacterSoundComponentInterface.h"
#include "NiagaraFunctionLibrary.h"

// ReSharper disable once CppUnusedIncludeDirective
#include UE_INLINE_GENERATED_CPP_BY_NAME(ALSXTAnimNotify_CharacterBreathEffects)

FString UAlsxtAnimNotify_CharacterBreathEffects::GetNotifyName_Implementation() const
{
	return FString("ALSXT Character Breath");
}

void UAlsxtAnimNotify_CharacterBreathEffects::Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(Mesh, Animation, EventReference);
	if (!IsValid(Mesh))
	{
		return;
	}
	if (!EnableCharacterBreathEffects)
	{
		return;
	}
	const auto* World{ Mesh->GetWorld() };
	if (World->WorldType != EWorldType::EditorPreview)
	{
		FGameplayTag Status{ IAlsxtCharacterInterface::Execute_GetCharacterStatus(Mesh->GetOwner()) };
		if (Status == ALSXTStatusTags::Dead)
		{
			return;
		}
		IAlsxtCharacterSoundComponentInterface::Execute_PlayBreathEffects(Mesh->GetOwner(), StaminaOverride);
	}
	else
	{
		if (PreviewSound)
		{
			UGameplayStatics::PlaySoundAtLocation(World, PreviewSound, Mesh->GetSocketLocation("head"), Mesh->GetSocketRotation("head"), 1.0f, 1.0f, 0.0f, nullptr, nullptr, Mesh->GetOwner());
		}
		if (PreviewParticle)
		{
			UNiagaraFunctionLibrary::SpawnSystemAttached(PreviewParticle, Mesh, "head", Mesh->GetSocketLocation("head"), Mesh->GetSocketRotation("head"), EAttachLocation::KeepWorldPosition, true, true, ENCPoolMethod::None, true);
		}
	}
}