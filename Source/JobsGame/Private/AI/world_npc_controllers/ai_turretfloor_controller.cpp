// Fill out your copyright notice in the Description page of Project Settings.


#include "ai_turretfloor_controller.h"


// Sets default values
Aai_turretfloor_controller::Aai_turretfloor_controller()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Aai_turretfloor_controller::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aai_turretfloor_controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

