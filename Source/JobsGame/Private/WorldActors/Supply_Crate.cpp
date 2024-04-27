// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/Supply_Crate.h"

// Sets default values
ASupply_Crate::ASupply_Crate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASupply_Crate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASupply_Crate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

