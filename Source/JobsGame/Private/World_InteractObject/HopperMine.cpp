// Fill out your copyright notice in the Description page of Project Settings.

#include "World_InteractObject/HopperMine.h"
#include "Engine/Light.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY(LogLoadResourceMine);
DEFINE_LOG_CATEGORY(LogHopper);

AHopperMine::AHopperMine()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	// Loading and Settings mine and Mine Component 
	HopperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HopperMesh")); 
	DetectedSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectedSphere"));
	ActiveSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ActivationSphere"));
	LightDetector = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightDetector"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HopperMesh(TEXT("/Game/World_InteractObject/HopperMine/Hoppers"));
	if (HopperMesh.Succeeded())
	{
		HopperMeshComponent->SetStaticMesh(HopperMesh.Object);
	}
	else
	{
		UE_LOG(LogLoadResourceMine, Warning, TEXT("Eror find object mesh"));
	}

	
	SetRootComponent(HopperMeshComponent);
	HopperMeshComponent->SetWorldScale3D(FVector(32.0f,32.0f,35.0f));

	// Settings component mine
	LightDetector->SetupAttachment(HopperMeshComponent);
	LightDetector->SetWorldLocation(FVector(0.0f, 0.0f, 0.32));
	LightDetector->Intensity = 10000.0f;	
	LightDetector->AttenuationRadius = 30.0f;
	LightDetector->IntensityUnits = ELightUnits::Lumens;	
	LightDetector->bAffectsWorld = true;	
	
} 


void AHopperMine::BeginPlay()
{
	Super::BeginPlay();

	HopperMeshComponent->SetSimulatePhysics(true);
	HopperMeshComponent->SetMassOverrideInKg(NAME_None, 50, true);
	


	
}


void AHopperMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHopperMine::ActivateMine()
{

}


void AHopperMine::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}


void AHopperMine::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}
