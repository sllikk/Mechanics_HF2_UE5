// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "FleshLightComponent.generated.h"
class USoundBase;

DECLARE_LOG_CATEGORY_EXTERN(LogFleshLight, Log, All);

UCLASS()
class UFleshLightComponent : public USpotLightComponent
{
	GENERATED_BODY()
	
public:
	
	void ToggleFleshLight();

protected:
	
	virtual void BeginPlay() override;	

	
private:

	bool blsFleshVisible;
	
};
