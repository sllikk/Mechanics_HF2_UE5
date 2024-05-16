// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "interact.generated.h"

// This class does not need to be modified.
UINTERFACE()
class Uinteract : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JOBSGAME_API Iinteract
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Interact(AActor* Actor) = 0;
	//virtual void CheatDebugHealth() = 0; 
	
};
