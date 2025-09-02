// MIT

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "AlsxtViewModelSkeletalMeshComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Rendering, Common), hidecategories=Object, config=Engine, editinlinenew, meta=(BlueprintSpawnableComponent))
class ALSXT_API UAlsxtViewModelSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	UAlsxtViewModelSkeletalMeshComponent();

protected:
	uint8 MaxOwnerAttempts = 10;
	UPROPERTY(EditDefaultsOnly, Category = "View Model")
	float DesiredFOV = 90.0f;
	
	TWeakObjectPtr<APlayerController> PlayerController;
	
	virtual void BeginPlay() override;
	virtual FMatrix GetRenderMatrix() const override;
};