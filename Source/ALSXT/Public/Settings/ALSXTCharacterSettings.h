// MIT

#pragma once

#include "CoreMinimal.h"
#include "Settings/AlsCharacterSettings.h"
#include "Settings/AlsxtLocomotionActionSettings.h"
#include "Settings/AlsxtOverlaySettings.h"
#include "Settings/AlsxtDefensiveModeSettings.h"
#include "Settings/AlsxtStatusSettings.h"
#include "Settings/AlsxtCharacterBreathEffectsSettings.h"
#include "Settings/AlsxtFootstepEffectSettings.h"
#include "Settings/AlsxtFreelookSettings.h"
#include "Settings/AlsxtHeldItemSettings.h"
#include "Settings/AlsxtProceduralAimSettings.h"
#include "Settings/AlsxtForegripPositionSettings.h"
#include "Settings/AlsxtVaultingSettings.h"
#include "Settings/AlsxtSlidingSettings.h"
#include "Settings/AlsxtFPEyeFocusSettings.h"
#include "Settings/AlsxtMeshRenderSettings.h"
#include "Settings/AlsxtMeshPaintingSettings.h"
#include "ALSXTCharacterSettings.generated.h"

UCLASS()
class ALSXT_API UALSXTCharacterSettings : public UAlsCharacterSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	FAlsxtLocomotionActionSettings LocomotionActionSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	FAlsxtOverlaySettings OverlaySettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	FAlsxtDefensiveModeSettings DefensiveMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	FAlsxtStatusSettings StatusSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	FAlsxtCharacterBreathEffectsSettings BreathEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	FAlsxtGeneralFootstepEffectSettings FootstepEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "First Person")
	FAlsxtFPEyeFocusSettings FirstPersonEyeFocus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Freelook")
	FAlsxtGeneralFreelookSettings Freelook;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions")
	FAlsxtGeneralVaultingSettings Vaulting;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions")
	FAlsxtGeneralSlidingSettings Sliding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	FAlsxtGeneralMeshRenderSettings MeshRender;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	FAlsxtGlobalGeneralMeshPaintingSettings MeshPainting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Held Item")
	FAlsxtGeneralHeldItemSettings HeldItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Procedural")
	FAlsxtProceduralAimSettings ProceduralAim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Procedural")
	FAlsxtForegripPositionSettings ForegripPosition;

	UALSXTCharacterSettings();
	
};
