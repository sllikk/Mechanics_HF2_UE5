// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "amunition.h"
#include "UObject/Interface.h"
#include "amunition_interface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class Uamunition_interface : public UInterface
{
	GENERATED_BODY()
};

class JOBSGAME_API Iamunition_interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	FORCEINLINE virtual EAmunition GetCurrentAmunition() const = 0;
	FORCEINLINE virtual int32 GetAmmunitionAmounth() const = 0;
	
};
