// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Supply_Crate.generated.h"
class UGeometryCollectionComponent;

UCLASS()
class JOBSGAME_API ASupply_Crate : public AActor
{
	GENERATED_BODY()
	
public:	

	ASupply_Crate();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
