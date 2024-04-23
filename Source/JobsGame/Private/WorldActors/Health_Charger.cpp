// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/Health_Charger.h"
#include "Components/BoxComponent.h"
#include "Player/MyCharacter.h"
#include "PlayerComponent/Health.h"

DEFINE_LOG_CATEGORY(LogHealthCharger);

// Sets default values
AHealth_Charger::AHealth_Charger()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthChargerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
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
	BoxComponent->SetupAttachment(HealthChargerMeshComponent);
	
}


void AHealth_Charger::BeginPlay()
{
	Super::BeginPlay();

	m_flMaxCharger = 50;
	m_flCharger = m_flMaxCharger;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AHealth_Charger::OnComponentBeginOverlap);
	// BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AHealth_Charger::OnComponentEndOverlap);

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



void AHealth_Charger::Interact(class AMyCharacter* Character)
{
	UHealthComponent* HealthComponent = Cast<UHealthComponent>(Character->GetComponentByClass(UHealthComponent::StaticClass()));
	if (HealthComponent != nullptr)
	{
		
		HealthComponent->RestoreHealth(GetCharge());		
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

void AHealth_Charger::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FName Name = *OtherActor->GetName();  
	UE_LOG(LogHealthCharger, Warning, TEXT("%s"), *OtherActor->GetName())
	
}




