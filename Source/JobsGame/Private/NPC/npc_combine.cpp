// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/npc_combine.h"


// Sets default values
Anpc_combine::Anpc_combine()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Anpc_combine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Anpc_combine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


