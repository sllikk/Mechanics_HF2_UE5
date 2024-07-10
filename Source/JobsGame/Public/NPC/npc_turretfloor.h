// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "npc_turretfloor.generated.h"

UCLASS()
class JOBSGAME_API Anpc_turretfloor : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Anpc_turretfloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
