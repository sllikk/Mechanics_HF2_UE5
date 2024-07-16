// Fill out your copyright notice in the Description page of Project Settings.


#include "turret_controller.h"


// Sets default values
Aturret_controller::Aturret_controller()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Aturret_controller::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aturret_controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

