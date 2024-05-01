// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericTeamAgentInterface.h"
#include "HopperMine.generated.h"
class UPointLightComponent;
class USkeletalMeshComponent;
class UAudioComponent;
class UParticleSystem;

DECLARE_LOG_CATEGORY_EXTERN(LogCombatMine, Log, All);

UCLASS(Config=Game)
class JOBSGAME_API AHopperMine : public AActor, public IGenericTeamAgentInterface 
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mine_SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintType, Category="PointLight", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> Detected_Light;

	UPROPERTY(EditAnywhere, Category="ParticleComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> ExplodeParticle;
	
public:	

	AHopperMine();
	
	virtual void PostInitializeComponents() override;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:	
	/*
	void Spawn();
	void OnRestore();
	void SetMineState( int iState );
	int GetMineState() { return m_iMineState; }
	bool IsValidLocation();
	void Flip( const FVector &vecForce, const AngularImpulse &torque );
	void SearchThink();
	void BounceThink();
	void SettleThink();
	void CaptiveThink();
	void ExplodeThink();
	void ExplodeTouch( CBaseEntity *pOther );
	void CavernBounceThink(); ///< an alternative style of bouncing used for the citizen modded bouncers
	bool IsAwake() { return m_bAwake; }
	void Wake( bool bWake );

*/

protected:

	int8			m_iHookN;
	int8			m_iHookE;
	int8			m_iHookS;
	int8			m_iAllHooks;
	int8			m_iMineState;
	int8			m_iFlipAttempts;
	int8			m_iModification;
	
	float		m_flIgnoreWorldTime;
	float		m_flExplosionDelay;
	float		m_flHookPositions;
	float		m_flLastPhysicsInfluenceTime;
	float		m_flTimeGrabbed;

	bool		m_bDisarmed;
	bool		m_bLockSilently;
	bool		m_bFoeNearest;
	bool		m_bPlacedByPlayer;
	bool		m_bHeldByPhysgun;

	
};
