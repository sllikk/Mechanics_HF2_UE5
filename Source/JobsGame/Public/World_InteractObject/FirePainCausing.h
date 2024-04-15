// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirePainCausing.generated.h"

UCLASS()
class JOBSGAME_API AFirePainCausing : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AFirePainCausing();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
