#pragma once

#include "Utility/AlsMath.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Engine/Texture2D.h"
#include "Engine/EngineTypes.h"
#include "Settings/AlsxtFootstepEffectSettings.h"
#include "GameplayTagContainer.h"
#include "AlsxtFootstepState.generated.h"

UENUM(BlueprintType)
enum class EAlsxtFootprintPhase : uint8
{
	Current,
	Previous,
};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtFootprintStatePhase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	TEnumAsByte<EPhysicalSurface> SurfaceType {0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	UTexture2D* TransferTexture = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	UTexture2D* TransferNormalTexture = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	UTexture2D* TransferDetailTexture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	UTexture2D* TransferDetailNormal = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float SurfaceTransferAmount{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float SurfaceTransferAcceptanceAmount{ 0.5f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = -2))
	float SurfaceTransferAcceptanceNormalScale{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float TransferAmount{ 0.5f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float TransferSaturationRate{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float TransferDesaturationRate{ 1.0f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float TransferDetailScale{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float TransferDetailNormalAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float TransferNormalScale{ 0.5f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FLinearColor TransferPrimaryColor{0.0f, 0.0f, 0.0f, 1.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	FLinearColor TransferSecondaryColor{0.0f, 0.0f, 0.0f, 1.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float TransferGrainSize{ 1.0f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float TransferWetness{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float TransferEmissiveAmount{ 0.0f };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float DecalDuration{4.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float DecalFadeOutDuration{2.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float DecalDurationModifierMin{ 1.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float DecalDurationModifierMax{ 4.0f };
};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtFootprintState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess))
	float FootSurfaceAlpha{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtFootprintStatePhase Current;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtFootprintStatePhase Previous;

};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtFootprintsState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtFootprintState Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAlsxtFootprintState Right;

};

USTRUCT(BlueprintType)
struct ALSXT_API FAlsxtFootwearDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Categories = "Als.Footwear Type"))
	FGameplayTag FootwearType { FGameplayTag::EmptyTag };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EPhysicalSurface> FootwearSoleSurfaceType{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* FootwearSoleTexture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* FootwearSoleNormalTexture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FootwearSoleNormalScale{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* FootwearSoleDetailTexture = nullptr;

};