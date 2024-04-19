// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Shared/damage.h"
#include "CustomDamage.generated.h"
class AActor;


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
	void SetCurrentDamageType(EDamageType TypeDamage);

	// Weapon is the weapon that did the attack
	// Attacker is the character who originated the attack (like a player or an AI).
	AActor* GetAttack() const{return m_Attacker;}
	void SetAttacker(AActor* pAttacker){m_Attacker = pAttacker;}

	// -------------------------------------------------------------------------------------------------- //
	// Inlines.
	// -------------------------------------------------------------------------------------------------- //
	FORCEINLINE float				GetDamage() const										{ return m_flDamage; } 
	FORCEINLINE void				SetDamage( float flDamage )								{ m_flDamage = flDamage; } 
	FORCEINLINE float				GetMaxDamage() const									{ return m_flMaxDamage; }
	FORCEINLINE void				SetMaxDamage( float flMaxDamage )						{ m_flMaxDamage = flMaxDamage; }
	FORCEINLINE void				ScaleDamage( float flScaleAmount )						{ m_flDamage *= flScaleAmount; }
	FORCEINLINE void				AddDamage( float flScaleAmount )						{ m_flDamage += flScaleAmount; }
	FORCEINLINE void				SubtractDamage( float flSubtractAmount )				{ m_flDamage -= flSubtractAmount; }
	FORCEINLINE FVector				GetDamageForce() const									{ return m_vecDamageForce; }
	FORCEINLINE void				SetDamageForce( const FVector &damageForce )			{ m_vecDamageForce = damageForce; }
	FORCEINLINE void				ScaleDamageForce( float flScaleAmount )					{ m_vecDamageForce *= flScaleAmount; }
	FORCEINLINE float				GetDamageForForceCalc() const							{ return m_flDamageForForce; }
	FORCEINLINE void				SetDamageForForceCalc( float flDamage )					{ m_flDamageForForce = flDamage; }
	FORCEINLINE FVector				GetDamagePosition() const								{ return m_vecDamagePosition; }
	FORCEINLINE void				SetDamagePosition( const FVector &damagePosition )		{ m_vecDamagePosition = damagePosition; }
	FORCEINLINE FVector				GetReportedPosition() const								{ return m_vecReportedPosition; }
	FORCEINLINE void				SetReportedPosition( const FVector &reportedPosition )	{ m_vecReportedPosition = reportedPosition; }

protected:

	UPROPERTY(EditAnywhere)
	EDamageType DamageType;
	UPROPERTY(EditAnywhere,  BlueprintReadOnly, Category = "Damage")
	TMap<EDamageType, FDamageTypeData> DataType;
	
protected:

	float							m_flDamage;
	float							m_flDamagePerSec;
	float							m_flMaxDamage;
	float							m_flBaseDamage;		// The damage amount before skill leve adjustments are made. Used to get uniform damage forces.
	float							m_flDamageForForce;
	FVector							m_vecDamageForce;
	FVector							m_vecDamagePosition;
	FVector							m_vecReportedPosition;	// Position players are told damage is coming from
	UPROPERTY()
	AActor*							m_Inflictor;
	UPROPERTY()	
	AActor*							m_Attacker;
	UPROPERTY()
	AActor*							m_Weapon;

private:

	UFUNCTION()
	void InitialDamageType();

};
