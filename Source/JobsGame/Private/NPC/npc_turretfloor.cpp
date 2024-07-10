// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/npc_turretfloor.h"


// Sets default values
Anpc_turretfloor::Anpc_turretfloor()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Anpc_turretfloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Anpc_turretfloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


