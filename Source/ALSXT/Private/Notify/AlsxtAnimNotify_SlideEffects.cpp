// MIT


#include "Notify/AlsxtAnimNotify_SlideEffects.h"

#include "AlsCharacter.h"
#include "AlsxtAnimationInstance.h"
#include "AlsxtCharacter.h"
#include "DrawDebugHelpers.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Animation/AnimInstance.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Notifies/AlsAnimNotify_FootstepEffects.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Utility/AlsConstants.h"
#include "Utility/AlsEnumUtility.h"
#include "Utility/AlsMacros.h"
#include "Utility/AlsMath.h"
#include "Utility/AlsUtility.h"
#include "Utility/AlsDebugUtility.h"

// ReSharper disable once CppUnusedIncludeDirective
#include UE_INLINE_GENERATED_CPP_BY_NAME(ALSXTAnimNotify_SlideEffects)

FString UAlsxtAnimNotify_SlideEffects::GetNotifyName_Implementation() const
{
	return FString("ALSXT Slide Effects");
}

void UAlsxtAnimNotify_SlideEffects::Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(Mesh, Animation, EventReference);

	if (!IsValid(Mesh) || !ALS_ENSURE(IsValid(SlideEffectsSettings)))
	{
		return;
	}

	const auto* Character{ Cast<AAlsCharacter>(Mesh->GetOwner()) };
	AAlsxtCharacter* ALSXTCharacter{ Cast<AAlsxtCharacter>(Mesh->GetOwner()) };

	if (IsValid(ALSXTCharacter) && IAlsxtCharacterInterface::Execute_GetCharacterLocomotionMode(Mesh->GetOwner()) == AlsLocomotionModeTags::InAir)
	{
		return;
	}

	const auto CapsuleScale{ IsValid(ALSXTCharacter) ? ALSXTCharacter->GetCapsuleComponent()->GetComponentScale().Z : 1.0f };

	const auto* World{ Mesh->GetWorld() };
	const auto* AnimationInstance{ Mesh->GetAnimInstance() };
	const auto* ALSXTAnimationInstance{ Cast<UAlsxtAnimationInstance>(Mesh->GetAnimInstance()) };

	const auto FootBoneName{FootBone == EAlsFootBone::Left ? UAlsConstants::FootLeftBoneName() : UAlsConstants::FootRightBoneName()};
	const auto FootTransform{Mesh->GetSocketTransform(FootBoneName)};

	const auto FootZAxis{
		FootTransform.TransformVectorNoScale(FootBone == EAlsFootBone::Left
												 ? SlideEffectsSettings->FootLeftZAxis
												 : SlideEffectsSettings->FootRightZAxis)
	};

	FHitResult Hit;
	FVector HitLocation;
	FVector HitNormal;
	TWeakObjectPtr<UPrimitiveComponent> HitComponent;
	TWeakObjectPtr<UPhysicalMaterial> HitPhysicalMaterial;
	TEnumAsByte<EPhysicalSurface> HitSurface;

#if ENABLE_DRAW_DEBUG
	const auto bDisplayDebug{ UAlsDebugUtility::ShouldDisplayDebugForActor(Mesh->GetOwner(), UAlsConstants::TracesDebugDisplayName()) };
#endif

	FCollisionQueryParams QueryParameters{ ANSI_TO_TCHAR(__FUNCTION__), true, Mesh->GetOwner() };
	QueryParameters.bReturnPhysicalMaterial = true;

	if (World->LineTraceSingleByChannel(Hit, FootTransform.GetLocation(),
		FootTransform.GetLocation() - FootZAxis *
		(SlideEffectsSettings->SurfaceTraceDistance * CapsuleScale),
		UEngineTypes::ConvertToCollisionChannel(SlideEffectsSettings->SurfaceTraceChannel),
		QueryParameters))
	{
		HitResult = Hit;
		HitLocation = HitResult.ImpactPoint;
		HitNormal = HitResult.ImpactNormal;
		HitComponent = HitResult.Component;
		HitPhysicalMaterial = HitResult.PhysMaterial;
		HitSurface = UGameplayStatics::GetSurfaceType(Hit);

#if ENABLE_DRAW_DEBUG
		if (bDisplayDebug)
		{
			UAlsDebugUtility::DrawLineTraceSingle(World, Hit.TraceStart, Hit.TraceEnd, Hit.bBlockingHit,
				Hit, { 0.333333f, 0.0f, 0.0f }, FLinearColor::Red, 10.0f);
		}
#endif
	}
	else
	{
		HitResult.ImpactPoint = FootTransform.GetLocation();
		Hit.ImpactPoint = FootTransform.GetLocation();
		HitResult.ImpactNormal = FVector::UpVector;
		Hit.ImpactNormal = FVector::UpVector;
		HitLocation = FootTransform.GetLocation();
		HitNormal = FVector::UpVector;
		HitComponent = nullptr;
		HitResult.Component = nullptr;
		HitPhysicalMaterial = nullptr;
		HitResult.PhysMaterial = nullptr;
		HitSurface = SurfaceType_Default;
	}

	const auto SurfaceType{ HitSurface };
	const auto* EffectSettings{ SlideEffectsSettings->Effects.Find(SurfaceType) };

	if (EffectSettings == nullptr)
	{
		for (const auto& Pair : SlideEffectsSettings->Effects)
		{
			EffectSettings = &Pair.Value;
			break;
		}

		if (EffectSettings == nullptr)
		{
			return;
		}
	}

	const auto FootstepLocation{ HitResult.ImpactPoint };

	const auto FootstepRotation{
		FRotationMatrix::MakeFromZY(HitResult.ImpactNormal,
									FootTransform.TransformVectorNoScale(FootBone == EAlsFootBone::Left
																			 ? SlideEffectsSettings->FootLeftYAxis
																			 : SlideEffectsSettings->FootRightYAxis)).ToQuat()
	};

#if ENABLE_DRAW_DEBUG
	if (bDisplayDebug)
	{
		DrawDebugCoordinateSystem(World, FootstepLocation, FootstepRotation.Rotator(),
			25.0f, false, 10.0f, 0, UAlsDebugUtility::DrawLineThickness);
	}
#endif

	if (bSpawnSound)
	{
		auto VolumeMultiplier{ SoundVolumeMultiplier };

		if (!bIgnoreSlideSoundBlockCurve && IsValid(AnimationInstance))
		{
			VolumeMultiplier *= 1.0f - UAlsMath::Clamp01(AnimationInstance->GetCurveValue(UAlsConstants::FootstepSoundBlockCurveName()));
		}

		if (FAnimWeight::IsRelevant(VolumeMultiplier) && IsValid(EffectSettings->Sound.LoadSynchronous()))
		{
			UAudioComponent* Audio{ nullptr };

			switch (EffectSettings->SoundSpawnType)
			{
			case EALSXTFootstepSoundSpawnType::SpawnAtTraceHitLocation:
				if (World->WorldType == EWorldType::EditorPreview)
				{
					UGameplayStatics::PlaySoundAtLocation(World, EffectSettings->Sound.Get(), FootstepLocation,
						VolumeMultiplier, SoundPitchMultiplier);
				}
				else
				{
					Audio = UGameplayStatics::SpawnSoundAtLocation(World, EffectSettings->Sound.Get(), FootstepLocation,
						FootstepRotation.Rotator(),
						VolumeMultiplier, SoundPitchMultiplier);
				}
				break;

			case EALSXTFootstepSoundSpawnType::SpawnAttachedToFootBone:
				Audio = UGameplayStatics::SpawnSoundAttached(EffectSettings->Sound.Get(), Mesh, FootBoneName, FVector::ZeroVector,
					FRotator::ZeroRotator, EAttachLocation::SnapToTarget,
					true, VolumeMultiplier, SoundPitchMultiplier);
				break;
			}
		}
	}

	if (bSpawnParticleSystem && IsValid(EffectSettings->ParticleSystem.LoadSynchronous()))
	{
		switch (EffectSettings->ParticleSystemSpawnType)
		{
		case EALSXTFootstepParticleEffectSpawnType::SpawnAtTraceHitLocation:
		{
			const auto ParticleSystemRotation{
				FootstepRotation * (FootBone == EAlsFootBone::Left
										? EffectSettings->ParticleSystemFootLeftRotationOffset
										: EffectSettings->ParticleSystemFootLeftRotationOffset).Quaternion()
			};

			const auto ParticleSystemLocation{
				FootstepLocation +
				ParticleSystemRotation.RotateVector(EffectSettings->ParticleSystemLocationOffset * CapsuleScale)
			};

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, EffectSettings->ParticleSystem.Get(),
				ParticleSystemLocation, ParticleSystemRotation.Rotator(),
				FVector::OneVector * CapsuleScale, true, true, ENCPoolMethod::AutoRelease);
		}
		break;

		case EALSXTFootstepParticleEffectSpawnType::SpawnAttachedToFootBone:
			UNiagaraFunctionLibrary::SpawnSystemAttached(EffectSettings->ParticleSystem.Get(), Mesh, FootBoneName,
				EffectSettings->ParticleSystemLocationOffset * CapsuleScale,
				EffectSettings->ParticleSystemFootLeftRotationOffset,
				FVector::OneVector * CapsuleScale, EAttachLocation::KeepRelativeOffset,
				true, ENCPoolMethod::AutoRelease);
			break;
		}
	}

}