// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BBT_HeadCrabTask.generated.h"


UCLASS()
class UBBT_HeadCrabTask : public UBTTaskNode
{
	GENERATED_BODY()


public:	

	UBBT_HeadCrabTask();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
