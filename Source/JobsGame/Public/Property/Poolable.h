// Fill out your copyright notice in the Description page of Project Settings.

//-------------------------------------------------------------------------------
/* this interface for only object pool class */
//-------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Poolable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UPoolable : public UInterface
{
	GENERATED_BODY()
};

class JOBSGAME_API IPoolable
{
	GENERATED_BODY()

public:

	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
	
};
