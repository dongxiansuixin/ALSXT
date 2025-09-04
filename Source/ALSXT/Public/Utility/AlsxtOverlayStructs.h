#pragma once

#include "NativeGameplayTags.h"
#include "Settings/AlsxtDefensiveModeSettings.h"
#include "Templates/SubclassOf.h"
#include "AlsxtOverlayStructs.generated.h"

class UAnimInstance;

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtOverlaySlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.OverlayMode", AllowPrivateAccess))
	FGameplayTag Overlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.OverlaySlot", AllowPrivateAccess))
	FGameplayTag Slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TSubclassOf<UAnimInstance> AnimInstance;

	bool operator==(const FAlsxtOverlaySlotInfo& other) const
	{
		return (other.Overlay == Overlay) && (other.Slot == Slot) && (other.AnimInstance->GetClass() == AnimInstance->GetClass());
	}
};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtOverlayInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.OverlayMode", AllowPrivateAccess))
	FGameplayTag Overlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.OverlaySlot", AllowPrivateAccess))
	TMap<UPARAM(meta=(Categories="Als.OverlaySlot")) FGameplayTag, TSubclassOf<UAnimInstance>> Slots;

	bool operator==(const FAlsxtOverlayInfo& other) const
	{
		return (other.Overlay == Overlay);
	}
};