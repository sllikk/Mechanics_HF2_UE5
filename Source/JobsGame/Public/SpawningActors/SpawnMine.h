// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnMine.generated.h"

UCLASS()
class JOBSGAME_API ASpawnMine : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASpawnMine();

protected:
	
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
