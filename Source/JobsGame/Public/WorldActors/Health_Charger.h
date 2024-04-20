// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Health_Charger.generated.h"
class AMyCharacter;


UCLASS(Config=Game)
class JOBSGAME_API AHealth_Charger : public AActor
{
	GENERATED_BODY()
	
public:	

	AHealth_Charger();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	

};
