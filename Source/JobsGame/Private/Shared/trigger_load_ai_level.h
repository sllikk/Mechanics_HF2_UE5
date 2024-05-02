// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "trigger_load_ai_level.generated.h"
class UBoxComponent;

UCLASS(MinimalAPI)
class Atrigger_load_ai_level : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="BoxCollision")
	TObjectPtr<UBoxComponent> Trigger;
	
public:	

	Atrigger_load_ai_level();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDetectionLevelBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FName Level_Name = "TEST_AI_MAP";

	
};
