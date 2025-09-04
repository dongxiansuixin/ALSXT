#pragma once

#include "Utility/AlsxtGameplayTags.h"
#include "AlsxtStatusState.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtStatusState
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.Status"))
		FGameplayTag CurrentStatus { ALSXTStatusTags::Normal };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0, ClampMax = 1))
		float CurrentHealth { 1.0 };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0, ClampMax = 1))
		float CurrentStamina { 1.0 };

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.Stamina"))
		FGameplayTag CurrentStaminaTag { ALSXTStaminaTags::Full };

		bool operator==(const FAlsxtStatusState& other) const
		{
			return (other.CurrentStatus == CurrentStatus) && (other.CurrentHealth == CurrentHealth) && (other.CurrentStamina == CurrentStamina) && (other.CurrentStaminaTag == CurrentStaminaTag);
		}
};

