// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "FlashLightComponent.generated.h"
class USoundBase;

DECLARE_LOG_CATEGORY_EXTERN(LogFlashLight, Log, All);

UCLASS()
class UFlashLightComponent : public USpotLightComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Sound", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> FlashLightSound;
	
public:
	
	void ToggleFlashLight();

protected:
	
	virtual void BeginPlay() override;	

	
private:

	bool blsFlashVisible;
	
};
