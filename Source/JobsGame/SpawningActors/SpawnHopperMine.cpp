// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningActors/SpawnHopperMine.h"

// Sets default values
ASpawnHopperMine::ASpawnHopperMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnHopperMine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnHopperMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

