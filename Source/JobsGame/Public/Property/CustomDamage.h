// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Shared/damage.h"
#include "CustomDamage.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCustomDamage, Log, All);

// DamageProperty
USTRUCT(BlueprintType)
struct FDamageTypeData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	float DamageMultiplayer; 
	UPROPERTY(BlueprintReadWrite)
	float DamageEffects;

	FDamageTypeData()
	   : DamageMultiplayer(0.0f),
		 DamageEffects(0.0f)
	{}

	FDamageTypeData(float damageMultiplayer, float effectDamage)
		: DamageMultiplayer(damageMultiplayer),DamageEffects(effectDamage)
	{}
};


UCLASS(Config=Game, meta=(ScriptName = "CustomDamage"))
class JOBSGAME_API UCustomDamage : public UDamageType
{
	GENERATED_BODY()
	
	
public:	

	UCustomDamage(const FObjectInitializer& ObjectInitializer);
	
	FDamageTypeData GetDamageTypeData() const;
	
public:

	UPROPERTY(EditAnywhere)
	EDamageType DamageType;
	UPROPERTY(EditAnywhere)
	TMap<EDamageType, FDamageTypeData> DataType;
	
	
};
