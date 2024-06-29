// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "amunition.generated.h"

UENUM(BlueprintType)
enum class EAmunition
{
	SMG1_BULLET,
	SHOTGUN_BULLET,
	PISTOL_BULLET,
	RPG_ROCKET,
	SMG1_GRENADE,
	
};

UCLASS()
class JOBSGAME_API Uamunition : public UUserDefinedEnum
{
	GENERATED_BODY()

	
};
