// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Ai_ScannerController.generated.h"

UCLASS()
class JOBSGAME_API AAi_ScannerController : public AAIController
{
	GENERATED_BODY()

public:

	AAi_ScannerController();

protected:

	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
};
