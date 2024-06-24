// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Game_Mode.generated.h"
class AImpactEffectHandler;
class Aobject_pool;

UCLASS()
class AGame_Mode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Effect", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AImpactEffectHandler> spawn_effect_class;

	UPROPERTY(EditAnywhere, Category="Effect", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<Aobject_pool> object_pool;
	
public:

	AGame_Mode();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:

	void Spawn() const;  
	void SpawnObjectPool();	

private:	
	

	
};
