// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "turret_controller.generated.h"

UCLASS()
class JOBSGAME_API Aturret_controller : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	Aturret_controller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
