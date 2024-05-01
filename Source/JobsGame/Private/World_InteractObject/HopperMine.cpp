// Fill out your copyright notice in the Description page of Project Settings.

#include "World_InteractObject/HopperMine.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystem.h"
#include "Shared/Resourse.h"

DEFINE_LOG_CATEGORY(LogCombatMine);

enum class EMineState
{
	MINE_STATE_DORMANT = 0,
	MINE_STATE_DEPLOY,		// Try to lock down and arm
	MINE_STATE_CAPTIVE,		// Held in the physgun
	MINE_STATE_ARMED,		// Locked down and looking for targets
	MINE_STATE_TRIGGERED,	// No turning back. I'm going to explode when I touch something.
	MINE_STATE_LAUNCHED,	// Similar. Thrown from physgun.
};
#define HOPPER_MINE_MAX_FLIPS 5

AHopperMine::AHopperMine()
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


void AHopperMine::PostInitializeComponents()
{
	Super::PostInitializeComponents();



}


void AHopperMine::BeginPlay()
{
	Super::BeginPlay();
	
}


void AHopperMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AHopperMine::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

