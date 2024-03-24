// Fill out your copyright notice in the Description page of Project Settings.


#include "World_InteractObject/HopperMine.h"

// Sets default values
AHopperMine::AHopperMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHopperMine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHopperMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

