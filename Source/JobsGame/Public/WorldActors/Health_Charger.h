// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Health_Charger.generated.h"
class AMyCharacter;
class UStaticMeshComponent;
class UBoxComponent;
class UPointLightComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogHealthCharger, Log, All);

UCLASS(Config=Game)
class JOBSGAME_API AHealth_Charger : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category="MeshComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> HealthChargerMeshComponent;

	UPROPERTY(VisibleAnywhere, Category="MeshComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere, Category="MeshComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> LightCharger;
	
public:	

	AHealth_Charger();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	

};
