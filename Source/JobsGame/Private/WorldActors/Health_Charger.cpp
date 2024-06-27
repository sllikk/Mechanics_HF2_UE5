// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/Health_Charger.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerComponent/Health.h"
#include "Shared/Resourse.h"

DEFINE_LOG_CATEGORY(LogHealthCharger);

// Sets default values
AHealth_Charger::AHealth_Charger()
{
	PrimaryActorTick.bCanEverTick = true;

	m_flInteractCharacter = 1;
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
	HealthChargerMeshComponent->SetWorldScale3D(FVector(28, 28, 28));

}


void AHealth_Charger::BeginPlay()
{
	Super::BeginPlay();

	m_flMaxCharger = 50;
	m_flCharger = m_flMaxCharger;
	
	// Load Resource
	TArray<FResourceLoad> ResourceToLoad = {
	FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/PickUp_Health_Cue"), nullptr},	
	FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/health_charge_Cue"), nullptr}	
	};
	for (FResourceLoad& Resource : ResourceToLoad)
	{
		Resource.LoadedResource = LoadObject<UObject>(nullptr, *Resource.ResourcePath);
		if (!Resource.LoadedResource)
		{
			UE_LOG(LogHealthCharger, Warning, TEXT("Error Loaded: %s"), *Resource.ResourcePath)
		}
	}
	for (const FResourceLoad& Resource : ResourceToLoad)
	{
		USoundBase* LoadSound = Cast<USoundBase>(Resource.LoadedResource);

		if (LoadSound != nullptr)
		{
			Health_ChargerSound.Add(LoadSound);
		}	
	}
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


void AHealth_Charger::DebugStation() const
{
	const FString strDebug = FString::Printf(TEXT("charger: %2.f"), GetCharge());	
	FVector  LocationDebug = GetActorLocation();
	LocationDebug.Z += 100.0f; 
	FColor Color = FColor::White;
	DrawDebugString(GetWorld(), LocationDebug, strDebug, nullptr, Color, 0.0f, true);

}


void AHealth_Charger::StartRestore(AActor* Actor) 
{
	float RestoreInterval = 0.15f;  
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
		m_flCharger = FMath::Clamp(m_flCharger -  m_flInteractCharacter, 0.0f, GetMaxCharger());

		if (HealthComponent->GetPlayerHealth() < HealthComponent->GetPlayerMaxHealth())
		{
			HealthComponent->RestoreHealth(m_flInteractCharacter);
		}
	}
}