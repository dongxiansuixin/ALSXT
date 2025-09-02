#pragma once

#include "Settings/ALSXTAcrobaticActionSettings.h"
#include "AlsxtAcrobaticActionComponentInterface.generated.h"

UINTERFACE(Blueprintable)
class UAlsxtAcrobaticActionComponentInterface : public UInterface {
	GENERATED_BODY()
};

class ALSXT_API IAlsxtAcrobaticActionComponentInterface {
	GENERATED_BODY()

public:

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Acrobatic Action Component Interface")
  UALSXTAcrobaticActionSettings* GetAcrobaticActionSettings();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Acrobatic Action Component Interface")
  bool CanPerformAcrobaticAction();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Acrobatic Action Component Interface")
  bool CanFlip();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Acrobatic Action Component Interface")
  bool CanWallJump();

  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Acrobatic Action Component Interface")
  bool CanWallRun();
};