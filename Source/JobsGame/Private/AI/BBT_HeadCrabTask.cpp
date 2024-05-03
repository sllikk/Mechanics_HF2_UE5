// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BBT_HeadCrabTask.h"

UBBT_HeadCrabTask::UBBT_HeadCrabTask()
{
}

EBTNodeResult::Type UBBT_HeadCrabTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
