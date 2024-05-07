// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Ai_ScannerController.generated.h"
class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAISenseConfig_Sight; 
class UAIPerceptionComponent;

UCLASS()
class JOBSGAME_API AAi_ScannerController : public AAIController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="AI_Sense", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAISenseConfig_Sight> Config_Sight;
	UPROPERTY(EditAnywhere, Category="AI_Sense", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

public:

	AAi_ScannerController(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//virtual void OnPossess(APawn* InPawn) override;

	//UFUNCTION()
	//void OnTargetPerception(AActor* Actor, FAIStimulus Stimulus);

public:

	UPROPERTY(Transient)
	TObjectPtr<UBehaviorTreeComponent> BTC;

	UPROPERTY(Transient)
	TObjectPtr<UBlackboardComponent> BBC;

public:

	
};
