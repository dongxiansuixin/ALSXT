// Fill out your copyright notice in the Description page of Project Settings.


#include "AlsxtLinkedAnimationInstance.h"

#include "AlsxtAnimationInstance.h"
#include "AlsxtCharacter.h"
#include "Utility/AlsMacros.h"

UAlsxtLinkedAnimationInstance::UAlsxtLinkedAnimationInstance()
{
	RootMotionMode = ERootMotionMode::IgnoreRootMotion;
	bUseMainInstanceMontageEvaluationData = true;
}

void UAlsxtLinkedAnimationInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ALSXTParent = Cast<UAlsxtAnimationInstance>(GetSkelMeshComponent()->GetAnimInstance());
	ALSXTCharacter = Cast<AAlsxtCharacter>(GetOwningActor());

#if WITH_EDITOR
	if (!GetWorld()->IsGameWorld())
	{
		// Use default objects for editor preview.

		if (!IsValid(ALSXTParent))
		{
			ALSXTParent = GetMutableDefault<UAlsxtAnimationInstance>();
		}

		if (!IsValid(ALSXTCharacter))
		{
			ALSXTCharacter = GetMutableDefault<AAlsxtCharacter>();
		}
	}
#endif
}

void UAlsxtLinkedAnimationInstance::NativeBeginPlay()
{
	ALS_ENSURE_MESSAGE(IsValid(ALSXTParent),
					TEXT("%s (%s) should only be used as a linked animation instance within the %s animation blueprint!"),
					ALS_GET_TYPE_STRING(UAlsxtLinkedAnimationInstance).GetData(), *GetClass()->GetName(),
					ALS_GET_TYPE_STRING(UAlsxtAnimationInstance).GetData());

	Super::NativeBeginPlay();
}