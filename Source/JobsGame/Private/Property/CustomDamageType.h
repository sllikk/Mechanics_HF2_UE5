// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "CustomDamageType.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCustomDamage, Log, All);

// Struct Damage Setting 
USTRUCT()
struct FDamageTypeData
{
	GENERATED_BODY()

	UPROPERTY(Blueprintable)
	float DamageMultiplayer;
	UPROPERTY(Blueprintable)
	float EffectDuration;

	FDamageTypeData(){};
	FDamageTypeData(float DamageMultiplayer, float EffectDuration)
	: DamageMultiplayer(DamageMultiplayer), EffectDuration(EffectDuration){}

};

// damage type
UENUM(Blueprintable)
enum class EDamageType : uint8
{
	DMG_FIRE			UMETA(DisplayName = "FireDamage"),	
	DMG_ELECTRIC		UMETA(DisplayName = "ElectricDamage"),	
	DMG_PHYSICS			UMETA(DisplayName = "PhysicsDamage"),	
	DMG_DROWN			UMETA(DisplayName = "WaterDamage"),	
	DMG_FALL			UMETA(DisplayName = "FallDamage"),	
	DMG_EXPLOSION		UMETA(DisplayName = "ExplosionDamage"),	
	DMG_WEAPON			UMETA(DisplayName = "ExplosionDamage"),

};


UCLASS()
class UCustomDamageType : public UDamageType
{
	GENERATED_BODY()

	
public:
	
	UCustomDamageType();

public:
	// Get data for the current damage type
	FDamageTypeData GetDamageTypeData() const;
	
		// Type Damage
    	UPROPERTY(EditAnywhere, Blueprintable, Category = "Damage")
    	EDamageType DamageType;
    
    	//Dictionary for storing data for each damage type
    	UPROPERTY(EditAnywhere, Blueprintable, Category = "Damage")
    	TMap<EDamageType, FDamageTypeData> DamageData;

	

};

