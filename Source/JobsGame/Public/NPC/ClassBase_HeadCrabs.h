// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ClassBase_HeadCrabs.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ClassBase_HeadCrab, Log, All);

UCLASS(Abstract)
class JOBSGAME_API AClassBase_HeadCrabs : public APawn
{
	GENERATED_BODY()

public:

	AClassBase_HeadCrabs();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	

	

};
