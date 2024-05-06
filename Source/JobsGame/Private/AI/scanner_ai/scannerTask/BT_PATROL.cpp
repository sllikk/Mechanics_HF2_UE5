// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_PATROL.h"

#include "NavigationSystem.h"
#include "AI/scanner_ai/Ai_ScannerController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_PATROL::UBT_PATROL()
{
	NodeName = "PatrolLocation";
}

EBTNodeResult::Type UBT_PATROL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetOwner())
	{
		return EBTNodeResult::Failed;
	}

	if (const AAi_ScannerController* contr = Cast<AAi_ScannerController>(OwnerComp.GetAIOwner()))
	{
		if (APawn* cscanner = contr->GetPawn())
		{
			const FVector& Origin = cscanner->GetActorLocation();

			if (const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation ResultLocation;

				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchLocation, ResultLocation))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ResultLocation.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
	
}
