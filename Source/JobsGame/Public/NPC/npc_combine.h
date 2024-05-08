// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "npc_combine.generated.h"



UCLASS()
class JOBSGAME_API Anpc_combine : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Anpc_combine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:

};
