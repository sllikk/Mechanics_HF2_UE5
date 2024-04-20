// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/Health_Charger.h"

DEFINE_LOG_CATEGORY(LogHealthCharger);

// Sets default values
AHealth_Charger::AHealth_Charger()
{
 	 PrimaryActorTick.bCanEverTick = true;

	HealthChargerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	FSoftObjectPath FindMesh(TEXT("/Game/World_InteractObject/HealthStation/health_charger"));
	UStaticMesh* StaticMesh = nullptr;

	if (FindMesh.IsValid())
	{
	     StaticMesh = Cast<UStaticMesh>(FindMesh.TryLoad());
    }
    if (StaticMesh != nullptr)
    {
		HealthChargerMeshComponent->SetStaticMesh(StaticMesh);			   
    }
    else
    {
		UE_LOG(LogHealthCharger, Warning, TEXT("Error Load: %s"), *FindMesh.ToString());
    }

	HealthChargerMeshComponent->SetWorldScale3D(FVector(40.0f,40.0f,40.0f));
	
	
}


void AHealth_Charger::BeginPlay()
{
	Super::BeginPlay();
	
}


void AHealth_Charger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

