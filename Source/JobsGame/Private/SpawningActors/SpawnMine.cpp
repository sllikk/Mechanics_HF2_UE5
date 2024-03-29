// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawningActors/SpawnMine.h"
#include "World_InteractObject/HopperMine.h"

DEFINE_LOG_CATEGORY(LogSpawnHopper);

ASpawnMine::ASpawnMine()
{
	
	PrimaryActorTick.bCanEverTick = true;

	DefaultSpawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DefaultMesh"));
	DefaultSpawnMesh->bHiddenInGame = true;

	FSoftObjectPath FindSpawnMesh(TEXT("/Game/LevelPrototyping/Cylinder_Spawn"));
	UStaticMesh* StaticMesh = nullptr;

	if (FindSpawnMesh.IsValid())
	{
		StaticMesh = Cast<UStaticMesh>(FindSpawnMesh.TryLoad());
	}
	if (StaticMesh != nullptr)
	{
		DefaultSpawnMesh->SetStaticMesh(StaticMesh);
	}
	else
	{
		UE_LOG(LogSpawnHopper, Warning, TEXT("Eror find spawn mesh!!!!!!"));
	}
	
}


void ASpawnMine::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();

	if (World)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		HopperMine = World->SpawnActor<AHopperMine>(AHopperMine::StaticClass(), SpawnLocation, SpawnRotation, SpawnParameters);
	}

	else
	{
		UE_LOG(LogSpawnHopper, Warning, TEXT("Eror Spawn"));
	}
}

