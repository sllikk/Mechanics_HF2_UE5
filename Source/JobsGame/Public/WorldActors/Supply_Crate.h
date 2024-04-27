// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Supply_Crate.generated.h"

UCLASS()
class JOBSGAME_API ASupply_Crate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASupply_Crate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
