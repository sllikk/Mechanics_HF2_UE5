// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/Debug_Object.h"

DEFINE_LOG_CATEGORY(LogDebug_Object)		
DEFINE_LOG_CATEGORY(LogDebug_ResourceObject)		

ADebug_Object::ADebug_Object()
{
	PrimaryActorTick.bCanEverTick = true;

	PrototypeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	
	FSoftObjectPath FindMesh(TEXT("/Game/LevelPrototyping/Meshes/Prototype"));	
	UStaticMesh* StaticMesh = nullptr;

	if (FindMesh.IsValid())
	{
		StaticMesh = Cast<UStaticMesh>(FindMesh.TryLoad());
	}
	if (StaticMesh != nullptr)
	{
		PrototypeMeshComponent->SetStaticMesh(StaticMesh);
	}
	else
	{
		UE_LOG(LogDebug_ResourceObject, Warning, TEXT("Eror find %s"), *FindMesh.ToString())
	}
	
}


void ADebug_Object::DebugPrototype()
{
	FString Weight = FString::Printf(TEXT("Weight object: %f"), PrototypeMeshComponent->)
	
}

void ADebug_Object::GetWeight()
{
}


void ADebug_Object::BeginPlay()
{
	Super::BeginPlay();
	
	PrototypeMeshComponent->SetSimulatePhysics(true);
	PrototypeMeshComponent->SetMassOverrideInKg(NAME_Actor, 35, false);

	
}


void ADebug_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);






}




