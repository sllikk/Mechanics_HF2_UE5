// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AI_MineController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

enum class EMineState
{
	MINE_STATE_DORMANT = 0,
	MINE_STATE_DEPLOY,		// Try to lock down and arm
	MINE_STATE_CAPTIVE,		// Held in the physgun
	MINE_STATE_ARMED,		// Locked down and looking for targets
	MINE_STATE_TRIGGERED,	// No turning back. I'm going to explode when I touch something.
	MINE_STATE_LAUNCHED,	// Similar. Thrown from physgun.
};

AAI_MineController::AAI_MineController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component"));
		SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
		SightConfig->SightRadius = 750.0f; 
		SightConfig->LoseSightRadius = 750.0f; 
		SightConfig->PeripheralVisionAngleDegrees = 360.0f; 
		SightConfig->DetectionByAffiliation.bDetectEnemies = true; 
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true; 
		SightConfig->DetectionByAffiliation.bDetectFriendlies = false; 
		SightConfig->SetMaxAge(0.0f);		
		PerceptionComponent->ConfigureSense(*SightConfig);
		PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
 
}

void AAI_MineController::BeginPlay()
{
	Super::BeginPlay();
		
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_MineController::TargetDetected);


}



void AAI_MineController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void AAI_MineController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}


void AAI_MineController::TargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogAIPerception, Warning, TEXT("%s"), *Actor->GetName())

}




