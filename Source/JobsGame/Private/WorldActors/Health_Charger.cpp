// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/Health_Charger.h"
#include "Components/PointLightComponent.h"
#include "Player/MyCharacter.h"
#include "PlayerComponent/Health.h"

DEFINE_LOG_CATEGORY(LogHealthCharger);

// Sets default values
AHealth_Charger::AHealth_Charger()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthChargerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
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
	}
	else
	{
		UE_LOG(LogHealthCharger, Warning, TEXT("Error Load: %s"), *FindMesh.ToString());
	}
	RootComponent = HealthChargerMeshComponent;
	HealthChargerMeshComponent->SetWorldScale3D(FVector(40.0f, 40.0f, 40.0f));
	LightCharger->SetupAttachment(HealthChargerMeshComponent);
}


void AHealth_Charger::BeginPlay()
{
	Super::BeginPlay();

	m_flMaxCharger = 50;
	m_flCharger = 10;

}


void AHealth_Charger::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AHealth_Charger::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	DebugStation();
	
}



void AHealth_Charger::Interact()
{
	 HealthComponent = FindComponentByClass<UHealthComponent>();
	HealthComponent->RegisterComponent();
	if (HealthComponent != nullptr)
	{
		if (HealthComponent->GetHealth() < HealthComponent->GetMaxHealth())
		{
			UE_LOG(LogHealthCharger, Warning, TEXT("Int"));
			HealthComponent->RestoreHealth(m_flCharger);
		}
	}
	else
	{

	}
	
}

void AHealth_Charger::DebugStation()
{
	const FString strDebug = FString::Printf(TEXT("charger: %2.f"), GetCharge());	
	FVector LocationDebug = GetActorLocation();
	LocationDebug.Z += 225.0f; 
	FColor Color = FColor::White;
	DrawDebugString(GetWorld(), LocationDebug, strDebug, nullptr, Color, 00, true);
	
	
}



