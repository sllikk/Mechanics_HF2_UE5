// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SpawnMine.generated.h"
class AHopperMine;
class UStaticMeshComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogSpawnHopper, Log, All);

UCLASS()
class JOBSGAME_API ASpawnMine : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Default spawn class", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<AHopperMine> HopperMine;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Default mesh")
	TObjectPtr<UStaticMeshComponent> DefaultSpawnMesh;

public:	
	
	ASpawnMine();

protected:
	
	virtual void BeginPlay() override;

public:	
	

};
