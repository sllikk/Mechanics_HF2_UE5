// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/combine_ai/AI_Combine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/npc_combine.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

AAI_Combine::AAI_Combine(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	/* BehaviorTree Initialise */
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	/* Sense PerceptionComponent */	
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));
	Config_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseConfig_Sight"));
	Config_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("SenseConfig_Hearing"));
	/*----------------------------------------------------------------------------------------------------------------------------------------*/
		Config_Sight->SightRadius = 1500.0f;	
		Config_Sight->SetMaxAge(10.0f);
		Config_Sight->PeripheralVisionAngleDegrees = 90.0f;  
		Config_Sight->LoseSightRadius = Config_Sight->SightRadius + 100.0f;
		Config_Sight->DetectionByAffiliation.bDetectEnemies = true;
		Config_Sight->DetectionByAffiliation.bDetectFriendlies = true;
		Config_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	/*----------------------------------------------------------------------------------------------------------------------------------------*/
		Config_Hearing->HearingRange = 1150.0f;	
		Config_Hearing->SetMaxAge(25.0f);	
		Config_Hearing->DetectionByAffiliation.bDetectEnemies = true;
		Config_Hearing->DetectionByAffiliation.bDetectFriendlies = false; 
		Config_Hearing->DetectionByAffiliation.bDetectNeutrals = true;

	// Config Sight //
	PerceptionComponent->ConfigureSense(*Config_Sight);
	PerceptionComponent->SetDominantSense(*Config_Sight->GetSenseImplementation());
	// Config Hearing // 
	PerceptionComponent->ConfigureSense(*Config_Hearing);
	PerceptionComponent->SetDominantSense(*Config_Hearing->GetSenseImplementation());
	
}


void AAI_Combine::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}


void AAI_Combine::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_Combine::OnTargetUpdate);
	
}
/*----------------------------------------------------------------------------------------------------------------------------------------*/

void AAI_Combine::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const Anpc_combine* npc_combine = Cast<Anpc_combine>(InPawn);

	if (npc_combine != nullptr && npc_combine->TreeAsset != nullptr)
	{
		BBC->InitializeBlackboard(*npc_combine->TreeAsset->BlackboardAsset);		
		BTC->StartTree(*npc_combine->TreeAsset);
	}

}
/*----------------------------------------------------------------------------------------------------------------------------------------*/

void AAI_Combine::OnTargetUpdate(AActor* Actor, FAIStimulus Stimulus)
{

}





