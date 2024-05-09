// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_PATROL.h"

#include "NavigationSystem.h"
#include "AI/combine_ai/AI_Combine.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_PATROL::UBT_PATROL(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "PatrolRandom";
	flSearch = 800;
}

// Patrol Random Location 
EBTNodeResult::Type UBT_PATROL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner()) // if GetAIOwner == nullptr return FailedTask
	{
		return EBTNodeResult::Failed;
	}

	if (const AAI_Combine* Controller = Cast<AAI_Combine>(OwnerComp.GetAIOwner()))
	{
		if (const APawn* npc_combine = Controller->GetPawn())
		{
			const FVector& Origin = npc_combine->GetActorLocation(); // Combine Location
			// Get NavigationMesh
			if (const UNavigationSystemV1* SystemNav = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation ResultLocation;
				// Get Random point Navmesh	
				if (SystemNav->GetRandomPointInNavigableRadius(Origin, flSearch, ResultLocation))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),ResultLocation.Location);  //Get key behavior tree
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // if point search return Succeeded this task
				return EBTNodeResult::Succeeded;
			}
		}
	}
		return EBTNodeResult::Failed;	
}
