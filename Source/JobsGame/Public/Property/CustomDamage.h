// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "CustomDamage.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCustomDamage, Log, All);

// DamageType
UENUM(BlueprintType, meta=(ScriptName = "ECustomDamage"))
enum class EDamageType
{
	DMG_FIRE				UMETA(DisplayName = "FireDamage"),
	DMG_ELECTRIC			UMETA(DisplayName = "ElectricDamage"),
	DMG_FALL				UMETA(DisplayName = "FallDamage"),
	DMG_DROWN				UMETA(DisplayName = "DrownDamage"),
	DMG_EXPLOSION			UMETA(DisplayName = "ExplosionDamage"),
	DMG_PHYSICS				UMETA(DisplayName = "PhysicsDamage"),
	DMG_WEAPON				UMETA(DisplayName = "WeaponDamage"),
	
};

// DamageProperty
USTRUCT(BlueprintType)
struct FDamageTypeData
{
	GENERATED_BODY()
	
	UPROPERTY(Blueprintable)
	float DamageMultiplayer; 
	UPROPERTY(Blueprintable)
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

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageType",  meta = (ScriptName = "CustomDamageType"))
	EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageTypeData")
	FDamageTypeData DamageTypeData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataType")
	TMap<EDamageType, FDamageTypeData> DataType;

	FDamageTypeData GetDamageTypeData() const;
	
	
};
