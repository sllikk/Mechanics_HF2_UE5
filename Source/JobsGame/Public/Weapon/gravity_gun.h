// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gravity_gun.generated.h"

UCLASS()
class JOBSGAME_API Agravity_gun : public AActor
{
	GENERATED_BODY()
	
public:	

	Agravity_gun();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
