// MIT


#include "Notify/ALSXTAnimNotifyState_HITrace.h"

#include "Utility/ALSXTGameplayTags.h"
#include "Interfaces/AlsxtCharacterInterface.h"
#include "Interfaces/AlsxtCombatInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "Utility/AlsUtility.h"

UALSXTAnimNotifyState_HITrace::UALSXTAnimNotifyState_HITrace()
{
	bIsNativeBranchingPoint = true;
}

FString UALSXTAnimNotifyState_HITrace::GetNotifyName_Implementation() const
{
	return FString::Format(TEXT("Held Time Attack Type: {0}"), {
							   FName::NameToDisplayString(UAlsUtility::GetSimpleTagName(OverlayMode).ToString(), false)
		});
}

void UALSXTAnimNotifyState_HITrace::NotifyBegin(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation,
	const float Duration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(Mesh, Animation, Duration, EventReference);

	if (IsValid(Mesh->GetOwner()) && Mesh->GetOwner()->GetClass()->ImplementsInterface(UAlsxtCharacterInterface::StaticClass()) && Mesh->GetOwner()->GetClass()->ImplementsInterface(UAlsxtCombatInterface::StaticClass()))
	{
		FALSXTCombatAttackTraceSettings TraceSettings;
		TraceSettings.Overlay = IAlsxtCharacterInterface::Execute_GetCharacterOverlayMode(Mesh->GetOwner());
		TraceSettings.ImpactType = ALSXTImpactTypeTags::Hit;
		TraceSettings.AttackType = ALSXTAttackMethodTags::Regular;
		TraceSettings.ImpactForm = ALSXTImpactFormTags::Blunt;
		TraceSettings.AttackStrength = AttackStrength;
		bool Found {false};

		IAlsxtCombatInterface::Execute_GetCombatHeldItemTraceLocations(Mesh->GetOwner(), Found, TraceSettings.Start, TraceSettings.End, TraceSettings.Radius);
		if (Found)
		{
			IAlsxtCombatInterface::Execute_BeginCombatAttackCollisionTrace(Mesh->GetOwner(), TraceSettings);
		}
	}
}

void UALSXTAnimNotifyState_HITrace::NotifyEnd(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(Mesh, Animation, EventReference);

	if (IsValid(Mesh->GetOwner()) && Mesh->GetOwner()->GetClass()->ImplementsInterface(UAlsxtCharacterInterface::StaticClass()) && Mesh->GetOwner()->GetClass()->ImplementsInterface(UAlsxtCombatInterface::StaticClass()))
	{
		IAlsxtCombatInterface::Execute_EndCombatAttackCollisionTrace(Mesh->GetOwner());
	}
}