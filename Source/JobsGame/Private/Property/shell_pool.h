// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Property/object_pool.h"
#include "shell_pool.generated.h"

UCLASS(MinimalAPI)
class Ashell_pool : public Aobject_pool
{
	GENERATED_BODY()

	Ashell_pool();

public:
	virtual void BeginPlay() override;


private:

	UPROPERTY()
	int32 imaxpool;

};
