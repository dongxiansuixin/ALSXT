#include "Settings/AlsxtAnimationInstanceSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ALSXTAnimationInstanceSettings)

UAlsxtAnimationInstanceSettings::UAlsxtAnimationInstanceSettings()
{
	InAir.GroundPredictionResponseChannels =
	{
		ECC_WorldStatic,
		ECC_WorldDynamic,
		ECC_Destructible
	};

	InAir.GroundPredictionSweepResponses.WorldStatic = ECR_Block;
	InAir.GroundPredictionSweepResponses.WorldDynamic = ECR_Block;
	InAir.GroundPredictionSweepResponses.Destructible = ECR_Block;
}

#if WITH_EDITOR
void UAlsxtAnimationInstanceSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	InAir.PostEditChangeProperty(PropertyChangedEvent);

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
