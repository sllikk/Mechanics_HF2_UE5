// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/npc_turret_floor.h"

#include "AI/EntityAiControllers/turret_controller.h"
#include "Components/PointLightComponent.h"
#include "Components/PoseableMeshComponent.h"


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
	detected_light->Intensity = 120;


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
	OutLocation = turret_mesh->GetSocketLocation("ViewSocket");
	OutRotation = GetActorRotation();
	OutRotation = turret_mesh->GetSocketTransform("ViewSocket", RTS_ParentBoneSpace).Rotator();	
}


void Anpc_turret_floor::LightUpdate(EDetectedState DetectedState)
{
	switch (DetectedState)
	{
	case EDetectedState::TURRET_EYE_DORMANT:
		detected_light->SetLightFColor(FColor::Green);
		break;
	case EDetectedState::TURRET_EYE_ALARM:
		detected_light->SetLightFColor(FColor::Red);
		break;
	case EDetectedState::TURRET_EYE_DISABLED:
		detected_light->SetLightFColor(FColor::Green);
		break;
	case EDetectedState::TURRET_EYE_DEAD: 
		 detected_light->SetLightFColor(FColor::Red);
		break;	
	case EDetectedState::TURRET_EYE_SEE_TARGET: 
		detected_light->SetLightFColor(FColor::Red);
		break;
	case EDetectedState::TURRET_EYE_SEEKING_TARGET:
		detected_light->SetLightFColor(FColor::Orange);
		break;
		default:
	break;
	}
}


