// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/damage.h"
#include "UObject/Interface.h"
#include "damageable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class Udamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JOBSGAME_API Idamageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void HandleDamage(int32 damage_amounth, EDamageType DamageType) = 0;
	
};
