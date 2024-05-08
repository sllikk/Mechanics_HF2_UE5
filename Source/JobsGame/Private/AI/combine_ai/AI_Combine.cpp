// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/combine_ai/AI_Combine.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC/npc_combine.h"
#include "Perception/AIPerceptionComponent.h"

AAI_Combine::AAI_Combine(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));	
	// Остальная инициализац

	
}


void AAI_Combine::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void AAI_Combine::BeginPlay()
{
	Super::BeginPlay();

}

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

void AAI_Combine::OnTargetUpdate(AActor* Actor, FAIStimulus Stimulus)
{

}



