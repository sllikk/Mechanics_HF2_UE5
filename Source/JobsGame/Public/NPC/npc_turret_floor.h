// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "npc_turret_floor.generated.h"

class UPointLightComponent;
class UPoseableMeshComponent;
class USoundBase;

enum ETurretState
{
	TURRET_SEARCHING,
	TURRET_AUTO_SEARCHING,
	TURRET_ACTIVE,
	TURRET_SUPPRESSING,
	TURRET_DEPLOYING,
	TURRET_RETIRING,
	TURRET_TIPPED,
	TURRET_SELF_DESTRUCTING,
	TURRET_STATE_TOTAL
};

enum EDetectedState
{
	TURRET_EYE_SEE_TARGET,			//Sees the target, bright and big
	TURRET_EYE_SEEKING_TARGET,		//Looking for a target, blinking (bright)
	TURRET_EYE_DORMANT,				//Not active
	TURRET_EYE_DEAD,				//Completely invisible
	TURRET_EYE_DISABLED,			//Turned off, must be reactivated before it'll deploy again (completely invisible)
	TURRET_EYE_ALARM,				// On side, but warning player to pick it back up
};

UCLASS(Blueprintable)
class JOBSGAME_API Anpc_turret_floor : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPoseableMeshComponent> turret_mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> detected_light;
	
public:
	// Sets default values for this pawn's properties
	Anpc_turret_floor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

public:

	// Think functions
	virtual void	Retire( void );
	virtual void	Deploy( void );
	virtual void	ActiveThink( void );
	virtual void	SearchThink( void );
	virtual void	AutoSearchThink( void );
	virtual void	TippedThink( void );
	virtual void	InactiveThink( void );
	virtual void	SuppressThink( void );
	virtual void	DisabledThink( void );
	virtual void	SelfDestructThink( void );
	virtual void	BreakThink( void );
		
	void LightUpdate(EDetectedState DetectedState);
	void SetTurretState(ETurretState State);
	
};
