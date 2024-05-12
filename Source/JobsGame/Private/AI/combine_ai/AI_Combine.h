// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AI_Combine.generated.h"
class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;

UCLASS()
class AAI_Combine : public AAIController
{
	GENERATED_BODY()

	// Sense Perception config
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category="Sense_ConfigHearing", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAISenseConfig_Hearing> Config_Hearing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category="Sense_ConfigSight", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAISenseConfig_Sight> Config_Sight;

public:

	AAI_Combine(const FObjectInitializer& ObjectInitializer);
	
protected:
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	UFUNCTION()
	void OnTargetUpdate(AActor* Actor, FAIStimulus Stimulus);

public:

	// Behavior tree setup
	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTreeComponent> BTC;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBlackboardComponent> BBC;

	
	


	
	
};
