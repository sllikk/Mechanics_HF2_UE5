// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "npc_combine.generated.h"
class USkeletalMeshComponent;
class UBehaviorTree;

DECLARE_LOG_CATEGORY_EXTERN(LogCombineClass, Log, All);

UCLASS()
class JOBSGAME_API Anpc_combine : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> combine_mesh;

	
public:
	// Sets default values for this character's properties
	Anpc_combine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called Hit Land
	virtual void Landed(const FHitResult& Hit) override;

public:

	// Behavior Tree this npc
	UPROPERTY(Transient, EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> TreeAsset;
	// RagDolls
	void RagDoll(bool Simulate);
	
#pragma region Getters_Setters 

	FORCEINLINE	USkeletalMeshComponent*		GetCombineMesh() const							 { return combine_mesh; }  
	FORCEINLINE float						GetMaxSpeedWalk() const							 { return m_flMaxSpeedWalk; }
	FORCEINLINE void						SetMaxSpeedWalk(float flMaxSpeedWalk)			 { m_flMaxSpeedWalk = flMaxSpeedWalk; }
	FORCEINLINE	float						GetMaxAcceleration() const						 { return m_flMaxAcceleration; }
	FORCEINLINE	void						SetMaxAcceleration(float fl_MaxAcceleration)	 { m_flMaxAcceleration =  fl_MaxAcceleration; } 
	FORCEINLINE	float						GetGravityScale() const							 { return m_flGravityScale; }
	FORCEINLINE	void						SetGravityScale(float fl_GravityScale)		 	 { m_flGravityScale = fl_GravityScale; }
	FORCEINLINE	float						GetAirControl() const							 { return m_flAirControl; }
	FORCEINLINE	void						SetAirControl(float fl_AirControl)				 { m_flAirControl = fl_AirControl; }
	FORCEINLINE	float						GetMaxSpeedFly() const							 { return m_flMaxSpeedFly; }
	FORCEINLINE	void						SetMaxSpeedFly(float fl_MaxSpeedFly)			 { m_flMaxSpeedFly = fl_MaxSpeedFly; }
	FORCEINLINE	float						GetMassCharacter() const						 { return m_flMassCombine; }
	FORCEINLINE	void						SetMassCharacter(float fl_MassCharacter)	 	 { m_flMassCombine = fl_MassCharacter; }
	FORCEINLINE int16						GetCurrentHealth() const						 { return m_iCurrentHealth; }				
	FORCEINLINE int16						GetMaxHealth() const							 { return m_iMaxHealth; }				
	FORCEINLINE	void						SetMaxHealth(int16 iMaxHealth) 					 { m_iMaxHealth = iMaxHealth; }					
	FORCEINLINE bool						ISDead() const									 { return  blsIsDead; }
	FORCEINLINE void						SetDead(bool bDead)								 { blsIsDead = bDead; } 
	FORCEINLINE bool						GetRagDoll() const								 { return blsRagDolls; }
	FORCEINLINE	void						SetRagDollState( bool bRagDoll)					 { blsRagDolls = bRagDoll; }
	FORCEINLINE FName						GetNameWeaponSocket() const						 { return WeaponSocket; }	
	#pragma endregion			

protected:

	const FName&	WeaponSocket = "GripPoint";
	bool		blsIsDead;
	bool		blsRagDolls;
	float		m_flMaxSpeedWalk;
	float		m_flMaxSpeedRun;
	float		m_flMaxAcceleration;        
	float		m_flGravityScale;
	float		m_flAirControl;
	float		m_flMaxSpeedFly;
	float		m_flMassCombine;
	float		m_maxFallDead;
		int16	m_iMaxHealth;
		int16	m_iCurrentHealth;

};
