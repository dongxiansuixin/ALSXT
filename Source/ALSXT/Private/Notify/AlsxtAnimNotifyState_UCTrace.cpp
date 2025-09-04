// MIT


#include "Notify/AlsxtAnimNotifyState_UCTrace.h"

#include "Utility/AlsxtGameplayTags.h"
#include "Interfaces/AlsxtCharacterInterface.h"
#include "Interfaces/AlsxtCombatInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "Utility/AlsUtility.h"

UAlsxtAnimNotifyState_UCTrace::UAlsxtAnimNotifyState_UCTrace()
{
	bIsNativeBranchingPoint = true;
}

FString UAlsxtAnimNotifyState_UCTrace::GetNotifyName_Implementation() const
{
	return FString::Format(TEXT("Unarmed Attack Type: {0}"), {
							   FName::NameToDisplayString(UAlsUtility::GetSimpleTagName(UnarmedAttackType).ToString(), false)
		});
}

void UAlsxtAnimNotifyState_UCTrace::NotifyBegin(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation,
	const float Duration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(Mesh, Animation, Duration, EventReference);
	const auto* World{ Mesh->GetWorld() };
	if (World->WorldType != EWorldType::EditorPreview)
	{
		if (IsValid(Mesh->GetOwner()))
		{
			TraceSettings.ImpactType = ALSXTImpactTypeTags::Hit;
			TraceSettings.AttackType = UnarmedAttackType;
			TraceSettings.ImpactForm = ALSXTImpactFormTags::Blunt;
			TraceSettings.AttackStrength = AttackStrength;
			if (Mesh->GetOwner()->Implements<UAlsxtCharacterInterface>())
			{
				TraceSettings.Overlay = IAlsxtCharacterInterface::Execute_GetCharacterOverlayMode(Mesh->GetOwner());

				IAlsxtCharacterInterface::Execute_SetCharacterMovementModeLocked(Mesh->GetOwner(), true);
			}
			if (Mesh->GetOwner()->Implements<UAlsxtCombatInterface>())
			{
				IAlsxtCombatInterface::Execute_GetCombatUnarmedTraceLocations(Mesh->GetOwner(), UnarmedAttackType, TraceSettings.Start, TraceSettings.End, TraceSettings.Radius);
				FString DebugMsg;
				IAlsxtCombatInterface::Execute_BeginCombatAttackCollisionTrace(Mesh->GetOwner(), TraceSettings);
			}

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Invalid")));
		}
	}
}

void UAlsxtAnimNotifyState_UCTrace::NotifyEnd(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(Mesh, Animation, EventReference);

	const auto* World{ Mesh->GetWorld() };
	if (World->WorldType != EWorldType::EditorPreview)
	{
		if (IsValid(Mesh->GetOwner()))
		{
			if (Mesh->GetOwner()->Implements<UAlsxtCombatInterface>())
			{
				IAlsxtCombatInterface::Execute_EndCombatAttackCollisionTrace(Mesh->GetOwner());
			}
			if (Mesh->GetOwner()->Implements<UAlsxtCharacterInterface>())
			{
				IAlsxtCharacterInterface::Execute_SetCharacterMovementModeLocked(Mesh->GetOwner(), false);
			}
		}
	}
}