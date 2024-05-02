// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISense.h"
#include "AI_MineController.generated.h"
class UAISenseConfig_Sight;

UCLASS()
class JOBSGAME_API AAI_MineController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="AISense_Sight", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UFUNCTION()
	void TargetDetected(AActor* Actor, FAIStimulus Stimulus);
	
public:

	AAI_MineController(const FObjectInitializer& ObjectInitializer);	



protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
};
