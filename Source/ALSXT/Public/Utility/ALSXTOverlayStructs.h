#pragma once

#include "NativeGameplayTags.h"
#include "Settings/ALSXTDefensiveModeSettings.h"
#include "Templates/SubclassOf.h"
#include "ALSXTOverlayStructs.generated.h"

class UAnimInstance;

USTRUCT(BlueprintType)
struct ALSXT_API FOverlaySlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.OverlayMode", AllowPrivateAccess))
	FGameplayTag Overlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.OverlaySlot", AllowPrivateAccess))
	FGameplayTag Slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TSubclassOf<UAnimInstance> AnimInstance;

	bool operator==(const FOverlaySlotInfo& other) const
	{
		return (other.Overlay == Overlay) && (other.Slot == Slot) && (other.AnimInstance->GetClass() == AnimInstance->GetClass());
	}
};

USTRUCT(BlueprintType)
struct ALSXT_API FOverlayInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.OverlayMode", AllowPrivateAccess))
	FGameplayTag Overlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.OverlaySlot", AllowPrivateAccess))
	TMap<UPARAM(meta=(Categories="Als.OverlaySlot")) FGameplayTag, TSubclassOf<UAnimInstance>> Slots;

	bool operator==(const FOverlayInfo& other) const
	{
		return (other.Overlay == Overlay);
	}
};