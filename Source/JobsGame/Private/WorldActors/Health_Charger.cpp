// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/Health_Charger.h"
#include "PlayerComponent/Health.h"

DEFINE_LOG_CATEGORY(LogHealthCharger);

// Sets default values
AHealth_Charger::AHealth_Charger()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthChargerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
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
	HealthChargerMeshComponent->SetWorldScale3D(FVector(25,25,25));
	
}


void AHealth_Charger::BeginPlay()
{
	Super::BeginPlay();

	m_flMaxCharger = 50;
	m_flCharger = m_flMaxCharger;
	
}


void AHealth_Charger::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer( HealthRestoreTimer);
}

void AHealth_Charger::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	DebugStation();
	
}


void AHealth_Charger::DebugStation()
{
	const FString strDebug = FString::Printf(TEXT("charger: %2.f"), GetCharge());	
	FVector LocationDebug = GetActorLocation();
	LocationDebug.Z += 100.0f; 
	FColor Color = FColor::White;
	DrawDebugString(GetWorld(), LocationDebug, strDebug, nullptr, Color, 00, true);
	
	
}

void AHealth_Charger::StartRestore(AActor* Actor)
{
	float RestoreInterval = 0.1f;  // Время в секундах между вызовами RestoreCharge
	GetWorld()->GetTimerManager().SetTimer( HealthRestoreTimer, [this, Actor]() { RestoreCharge(Actor); }, RestoreInterval, true);
}

void AHealth_Charger::StopRestore()
{
	
}

void AHealth_Charger::Interact(AActor* Actor)
{
	StartRestore(Actor);
	
}


void AHealth_Charger::RestoreCharge(AActor* Actor)
{
	UHealthComponent* HealthComponent = Cast<UHealthComponent>(Actor->GetComponentByClass(UHealthComponent::StaticClass()));
	if (HealthComponent != nullptr && GetCharge() > 0)
	{
		float Charger = 1;
		m_flCharger = FMath::Clamp(m_flCharger - Charger, 0.0f, GetMaxCharger());
		if (HealthComponent->GetHealth() < HealthComponent->GetMaxHealth())
		{
			HealthComponent->RestoreHealth(Charger);
		}
	}
	
}


	




