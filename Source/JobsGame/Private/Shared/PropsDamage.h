// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PropsDamage.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPropsDamage : public UInterface
{
	GENERATED_BODY()
};


class JOBSGAME_API IPropsDamage
{
	GENERATED_BODY()

public:

	virtual void ApplyDamage(float Damage, FVector HitLocation) = 0;

};
