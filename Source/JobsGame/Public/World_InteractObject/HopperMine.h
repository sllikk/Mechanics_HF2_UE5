// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HopperMine.generated.h"
class USkeletalMeshComponent;

UCLASS()
class JOBSGAME_API AHopperMine : public AActor
{
	GENERATED_BODY()
	
public:	
	AHopperMine();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
