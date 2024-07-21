// Fill out your copyright notice in the Description page of Project Settings.


#include "turret_controller.h"
#include "Components/PoseableMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NPC/npc_turret_floor.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
Aturret_controller::Aturret_controller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.Get())
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Perception = ObjectInitializer.CreateDefaultSubobject<UAIPerceptionComponent>(this, TEXT("PerceptionComponent"));	
	SetPerceptionComponent(*Perception);

	Config_Sight = ObjectInitializer.CreateDefaultSubobject<UAISenseConfig_Sight>(this, TEXT("ConfigSight"));	
	Config_Sight->SightRadius = 1600.0f;
	Config_Sight->LoseSightRadius = Config_Sight->SightRadius + 100.0f;
	Config_Sight->DetectionByAffiliation.bDetectEnemies = true;
	Config_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Config_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	Config_Sight->PeripheralVisionAngleDegrees = 45.0f;
	Config_Sight->SetMaxAge(1);
	
	Perception->SetDominantSense(*Config_Sight->GetSenseImplementation());
	Perception->ConfigureSense(*Config_Sight);

	AAIController::SetPawn(PtrNpcTurret_Floor);
	
}

// Called when the game starts or when spawned
void Aturret_controller::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void Aturret_controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (TurretState)
	{
	case ETurretState::TURRET_ACTIVE:
		ActiveThink();
		break;
	case ETurretState::TURRET_SEARCHING:
		SearchThink();
		break;
	case ETurretState::TURRET_AUTO_SEARCHING:
		AutoSearchThink();
		break;	
	case ETurretState::TURRET_SUPPRESSING:
		SuppressThink();
		break;
	case ETurretState::TURRET_RETIRING:	
		Retire();	
		break;
	case ETurretState::TURRET_SELF_DESTRUCTING:
		SelfDestructThink();
		break;	
	case ETurretState::TURRET_TIPPED:
		TippedThink();
		break;	
	default:
	break;

	}
	
}


void Aturret_controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PtrNpcTurret_Floor = Cast<Anpc_turret_floor>(InPawn);

	if( PtrNpcTurret_Floor )
	{
		Perception->OnTargetPerceptionUpdated.AddDynamic(this, &Aturret_controller::OntargetPerceptionUpdate);
	}
	
}

void Aturret_controller::OntargetPerceptionUpdate(AActor* OtherActor, FAIStimulus Stimulus)
{

	if (Stimulus.WasSuccessfullySensed())
	{
		ptrTargetActor = OtherActor;
		SetTurretState(ETurretState::TURRET_SEARCHING);	

	}
	else
	{
		ptrTargetActor = nullptr;
		SetTurretState(ETurretState::TURRET_AUTO_SEARCHING);		
	}

}

void Aturret_controller::Retire()
{
	
	
}

void Aturret_controller::ActiveThink()
{

}

void Aturret_controller::SearchThink()
{
	if (ptrTargetActor)
	{
		const FVector& AI_LOCATION = GetPawn()->GetActorLocation();
		const FVector& TriggerLocation = ptrTargetActor->GetActorLocation();

		RotatorZ.Yaw = UKismetMathLibrary::FindLookAtRotation(AI_LOCATION, TriggerLocation).Yaw - 90;
		
		const FRotator& CurrentRotate = PtrNpcTurret_Floor->GetPoseableMesh()->GetBoneRotationByName("body", EBoneSpaces::Type::WorldSpace);
		const FRotator& NewRotator = FMath::RInterpTo(CurrentRotate, RotatorZ, GetWorld()->GetDeltaSeconds(), 50);
		
		PtrNpcTurret_Floor->GetPoseableMesh()->SetBoneRotationByName("body", FRotator(CurrentRotate.Pitch, NewRotator.Yaw, CurrentRotate.Roll), EBoneSpaces::Type::WorldSpace);
		UE_LOG(LogActor, Warning, TEXT("BODY  pitch: %2.f, roll: %2.f, yaw: %2.f"), CurrentRotate.Pitch, CurrentRotate.Roll, NewRotator.Yaw)

	}
	
}

void Aturret_controller::AutoSearchThink()
{

}

void Aturret_controller::TippedThink()
{

}

void Aturret_controller::InactiveThink()
{

}

void Aturret_controller::SuppressThink()
{

}

void Aturret_controller::DisabledThink()
{

}

void Aturret_controller::SelfDestructThink()
{

}

void Aturret_controller::BreakThink()
{

}


void Aturret_controller::SetTurretState(ETurretState State)
{
	TurretState = State;
}
