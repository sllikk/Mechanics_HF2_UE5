// Fill out your copyright notice in the Description page of Project Settings.

#include "Ai_ScannerController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AAi_ScannerController::AAi_ScannerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Behavior tree for ai
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	Config_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI_Sight"));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Ai"));
	Config_Sight->SightRadius = 1500.0f;
	Config_Sight->LoseSightRadius = 1800.0f;
	Config_Sight->PeripheralVisionAngleDegrees = 180.0f;
	Config_Sight->DetectionByAffiliation.bDetectEnemies = true;
	Config_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Config_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AIPerceptionComponent->ConfigureSense(*Config_Sight);
	AIPerceptionComponent->SetDominantSense(*Config_Sight->GetSenseImplementation());
	
}

void AAi_ScannerController::BeginPlay()
{
	Super::BeginPlay();

	//PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAi_ScannerController::OnTargetPerception);
}

void AAi_ScannerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
void AAi_ScannerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	 const Anpc_scanner* npc_Cscanner = Cast<Anpc_scanner>(InPawn);
	
	if (npc_Cscanner != nullptr && npc_Cscanner->TreeAsset != nullptr)
	{
		BBC->InitializeBlackboard(*npc_Cscanner->TreeAsset->BlackboardAsset);
		BTC->StartTree(*npc_Cscanner->TreeAsset);
	}
	

}

void AAi_ScannerController::OnTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{


}
*/
