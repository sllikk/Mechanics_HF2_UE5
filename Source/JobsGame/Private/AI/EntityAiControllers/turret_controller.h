// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "turret_controller.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class Anpc_turret_floor;

enum ETurretState
{
	TURRET_SEARCHING,
	TURRET_AUTO_SEARCHING,
	TURRET_ACTIVE,
	TURRET_SUPPRESSING,
	TURRET_RETIRING,
	TURRET_TIPPED,
	TURRET_SELF_DESTRUCTING,
};

UCLASS()
class JOBSGAME_API Aturret_controller : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="AI", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> Perception;

	UPROPERTY(VisibleAnywhere, Category="AI", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAISenseConfig_Sight> Config_Sight;
	
	
public:
	// Sets default values for this actor's properties
	Aturret_controller(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OntargetPerceptionUpdate(AActor* OtherActor, FAIStimulus Stimulus);
		
public:

	// Think functions
	virtual void	Retire( void );
	virtual void	ActiveThink( void );
	virtual void	SearchThink( void );
	virtual void	AutoSearchThink( void );
	virtual void	TippedThink( void );
	virtual void	InactiveThink( void );
	virtual void	SuppressThink( void );
	virtual void	DisabledThink( void );
	virtual void	SelfDestructThink( void );
	virtual void	BreakThink( void );

	FORCEINLINE	void SetTurretState(ETurretState State);

private:

	UPROPERTY(EditAnywhere, Category="NPC" ,BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<Anpc_turret_floor> PtrNpcTurret_Floor;

	FRotator RotatorZ;
	
	UPROPERTY()
	TObjectPtr<AActor> ptrTargetActor;

	ETurretState TurretState;
	
	
};
