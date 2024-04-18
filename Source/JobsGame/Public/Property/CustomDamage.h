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

public:
	
	FDamageTypeData GetDamageTypeData() const;
	EDamageType GetCurrentDamageType() const;

	UFUNCTION(BlueprintType, Category="DamageType")
	FORCEINLINE void SetCurrentDamageType(EDamageType TypeDamage);
	UFUNCTION(BlueprintType, Category="DamageType")
	FORCEINLINE float GetDamage() const;
	UFUNCTION(BlueprintType, Category="DamageType")
	FORCEINLINE void SetDamage( float Damage );
	UFUNCTION(BlueprintType, Category="DamageType")
	FORCEINLINE float GetMaxDamage() const;
	UFUNCTION(BlueprintType, Category="DamageType")
	FORCEINLINE void SetMaxDamage( float MaxDamage );
	UFUNCTION(BlueprintType, Category="DamageType")
	FORCEINLINE void ScaleDamage( float ScaleAmount );
	UFUNCTION(BlueprintType, Category="DamageType")
	FORCEINLINE void AddDamage( float AddAmount );
	

	
protected:

	UPROPERTY(EditAnywhere)
	EDamageType DamageType;
	UPROPERTY(EditAnywhere,  BlueprintReadOnly, Category = "Damage")
	TMap<EDamageType, FDamageTypeData> DataType;
	
protected:

	float	m_Damage;
	float	m_DamagePerSec;
	float	m_MaxDamage;
	float	m_flBaseDamage;		



	
private:

	UFUNCTION()
	void InitialDamageType();
};
