// Fill out your copyright notice in the Description page of Project Settings.


#include "World_InteractObject/FlameBarrel.h"

// Sets default values
AFlameBarrel::AFlameBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlameBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlameBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

