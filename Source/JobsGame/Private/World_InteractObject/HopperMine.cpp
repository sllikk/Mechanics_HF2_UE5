// Fill out your copyright notice in the Description page of Project Settings.

#include "World_InteractObject/HopperMine.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY(LogLoadResourceMine);
DEFINE_LOG_CATEGORY(LogHopper);

AHopperMine::AHopperMine()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	HopperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HopperMesh")); 
	DetectedSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectedSphere"));
	ActiveSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ActivationSphere"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HopperMesh(TEXT("/Game/World_InteractObject/HopperMine/Hoppers"));
	if (HopperMesh.Succeeded())
	{
		HopperMeshComponent->SetStaticMesh(HopperMesh.Object);
	}
	else
	{
		UE_LOG(LogLoadResourceMine, Warning, TEXT("Eror find object mesh"));
	}
	
}


void AHopperMine::BeginPlay()
{
	Super::BeginPlay();
	
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
