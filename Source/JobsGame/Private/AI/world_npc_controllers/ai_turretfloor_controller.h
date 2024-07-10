// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ai_turretfloor_controller.generated.h"

UCLASS()
class JOBSGAME_API Aai_turretfloor_controller : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	Aai_turretfloor_controller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
