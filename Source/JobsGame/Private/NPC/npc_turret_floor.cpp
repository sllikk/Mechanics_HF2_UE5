// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/npc_turret_floor.h"
#include "Components/PointLightComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


// Sets default values
Anpc_turret_floor::Anpc_turret_floor()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	turret_mesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Turret_Mesh"));
	RootComponent = turret_mesh;

	turret_mesh->SetWorldScale3D(FVector(0.9f, 0.9f, 0.9f));
	
	const FSoftObjectPath ObjectPath(TEXT("/Game/World_InteractObject/Turret/turret_floor_model"));
	static USkeletalMesh* LoadSkeletal = nullptr;
	if (ObjectPath.IsValid())
	{
		LoadSkeletal = Cast<USkeletalMesh>(ObjectPath.TryLoad());
	} 
	if (LoadSkeletal != nullptr)
	{
		turret_mesh->SetSkinnedAsset(LoadSkeletal);
	}
	
	detected_light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Detected_Light"));
	detected_light->SetupAttachment(turret_mesh);
	detected_light->SetVisibility(true);
	detected_light->AttenuationRadius = 60.0f;
	detected_light->Intensity = 150;
	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	Config_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Config_Sight"));
	Config_Sight->SightRadius = 1500.0f;
	Config_Sight->PeripheralVisionAngleDegrees = 15.0f;
	Config_Sight->SetMaxAge(5.0f);
	Config_Sight->LoseSightRadius = Config_Sight->SightRadius + 150;
	Config_Sight->DetectionByAffiliation.bDetectEnemies = true;
	Config_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Config_Sight->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->SetDominantSense(*Config_Sight->GetSenseImplementation());
	PerceptionComponent->ConfigureSense(*Config_Sight);
	
}

// Called when the game starts or when spawned
void Anpc_turret_floor::BeginPlay()
{
	Super::BeginPlay();

	detected_light->AttachToComponent(turret_mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, "Light_Detected");
}

// Called every frame
void Anpc_turret_floor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void Anpc_turret_floor::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	//Super::GetActorEyesViewPoint(OutLocation, OutRotation);

	OutLocation = turret_mesh->GetSocketLocation("ViewSocket");
	OutRotation = GetActorRotation();
	OutRotation = turret_mesh->GetSocketTransform("ViewSocket", RTS_ParentBoneSpace).Rotator();
	
	
}

void Anpc_turret_floor::Retire()
{
}

void Anpc_turret_floor::Deploy()
{
}

void Anpc_turret_floor::ActiveThink()
{
}

void Anpc_turret_floor::SearchThink()
{
}

void Anpc_turret_floor::AutoSearchThink()
{
}

void Anpc_turret_floor::TippedThink()
{
}

void Anpc_turret_floor::InactiveThink()
{
}

void Anpc_turret_floor::SuppressThink()
{
}

void Anpc_turret_floor::DisabledThink()
{
}

void Anpc_turret_floor::SelfDestructThink()
{
}

void Anpc_turret_floor::BreakThink()
{
}

void Anpc_turret_floor::LightUpdate()
{
}

void Anpc_turret_floor::SetTurretState(ETurretState State)
{
}


