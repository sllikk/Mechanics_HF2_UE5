// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlameBarrel.generated.h"

UCLASS()
class JOBSGAME_API AFlameBarrel : public AActor
{
	GENERATED_BODY()
	
public:	

	AFlameBarrel();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
