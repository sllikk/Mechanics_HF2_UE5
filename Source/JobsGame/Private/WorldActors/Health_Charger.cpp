// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/Health_Charger.h"
#include "Components/BoxComponent.h"
#include "Components/LightComponent.h"
#include "Components/PointLightComponent.h"

DEFINE_LOG_CATEGORY(LogHealthCharger);

// Sets default values
AHealth_Charger::AHealth_Charger()
{
 	 PrimaryActorTick.bCanEverTick = false;

	HealthChargerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	LightCharger = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	const FSoftObjectPath FindMesh(TEXT("/Game/World_InteractObject/HealthStation/health_charger"));
	UStaticMesh* StaticMesh = nullptr;

	if (FindMesh.IsValid())
	{
	     StaticMesh = Cast<UStaticMesh>(FindMesh.TryLoad());
    }
    if (StaticMesh != nullptr)
    {
		HealthChargerMeshComponent->SetStaticMesh(StaticMesh);			   
		HealthChargerMeshComponent->SetupAttachment(RootComponent);
    }
    else
    {
		UE_LOG(LogHealthCharger, Warning, TEXT("Error Load: %s"), *FindMesh.ToString());
    }

	HealthChargerMeshComponent->SetWorldScale3D(FVector(40.0f,40.0f,40.0f));
	BoxComponent->SetupAttachment(HealthChargerMeshComponent);
	LightCharger->SetupAttachment(HealthChargerMeshComponent);

}


void AHealth_Charger::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHealth_Charger::OnBoxBeginOverlap);
}


void AHealth_Charger::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AHealth_Charger::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FName Name = *OtherActor->GetName();
	UE_LOG(LogHealthCharger, Warning, TEXT("Overlap: %s"), *Name.ToString())
}

