// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "hopper_mine.generated.h"
class USkeletalMeshComponent;
class UPointLightComponent;
class UParticleSystem;

UCLASS()
class JOBSGAME_API Ahopper_mine : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mine_SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintType, Category="PointLight", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> Detected_Light;

	UPROPERTY(EditAnywhere, Category="ParticleComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> ExplodeParticle;
	
public:

	Ahopper_mine();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
public:
	
	
	void	SetMineState( int iState );
	int		GetMineState() { return m_iMineState; }
	static	void	Flip( const FVector &vecForce, const FVector& AngularImpulce);
	void	SearchThink();
	void	BounceThink();
	void	 SettleThink();
	void	CaptiveThink();
	void	ExplodeThink();
	void	ExplodeTouch(AActor *pOther);
	bool	IsAwake() { return m_bAwake; }
	void	Wake( bool bWake );




protected:

	int16			m_iHookN;
	int16			m_iHookE;
	int16			m_iHookS;
	int16			m_iAllHooks;
	int16			m_iMineState;
	int16			m_iFlipAttempts;
	int16			m_iModification;
	
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
	bool		m_bAwake;
	
	FName      LightSocket = "LightSocket";
};
