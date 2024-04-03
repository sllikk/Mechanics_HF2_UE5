// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/Debug_Object.h"

// Sets default values
ADebug_Object::ADebug_Object()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADebug_Object::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebug_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

