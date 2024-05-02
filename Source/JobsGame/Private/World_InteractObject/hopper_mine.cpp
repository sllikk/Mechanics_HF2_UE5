// Fill out your copyright notice in the Description page of Project Settings.


#include "World_InteractObject/hopper_mine.h"

#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystem.h"
#define HOPPER_MINE_MAX_FLIPS 5


Ahopper_mine::Ahopper_mine()
{
	PrimaryActorTick.bCanEverTick = true;

	// Default SubObject
	Mine_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	Detected_Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	
	// Load Mesh
	static const FSoftObjectPath FinderMesh(TEXT("/Game/World_InteractObject/HopperMine/Combine_mine"));
	USkeletalMesh* SkeletalMesh = nullptr;
	if (FinderMesh.IsValid())
	{
		SkeletalMesh = Cast<USkeletalMesh>(FinderMesh.TryLoad());
	}
	if (SkeletalMesh != nullptr)
	{
		Mine_SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
	}

	// Load Partecles 
	static const FSoftObjectPath FinderParticle(TEXT("/Game/VFX/Particles/Explosion/Hopper_Explosion"));
	UParticleSystem* FoundParticle = nullptr;

	if(FinderParticle.IsValid())
	{
		FoundParticle = Cast<UParticleSystem>(FinderParticle.TryLoad());
	}
	if (FoundParticle != nullptr)
	{
		ExplodeParticle = FoundParticle;
	}

	SetRootComponent(Mine_SkeletalMesh);
	Mine_SkeletalMesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	
	
}

void Ahopper_mine::BeginPlay()
{
	Super::BeginPlay();
	
}

void Ahopper_mine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void Ahopper_mine::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


