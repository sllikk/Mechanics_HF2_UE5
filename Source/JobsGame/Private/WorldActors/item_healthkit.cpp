// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/item_healthkit.h"

#include "Kismet/GameplayStatics.h"

Aitem_healthkit::Aitem_healthkit()
{
	healthkit_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	healthkit_mesh->SetWorldScale3D(FVector(0.015f, 0.015f, 0.015f));
	RootComponent = healthkit_mesh;
	
	const FSoftObjectPath FindMesh(TEXT("/Game/WorldActors/RestoreKits/HealthKit/health_kit"));
	static TObjectPtr<UStaticMesh> LoadMesh = nullptr;

	if (FindMesh.IsValid())
	{
		LoadMesh = Cast<UStaticMesh>(FindMesh.TryLoad());
	}
	if (LoadMesh != nullptr)
	{
		healthkit_mesh->SetStaticMesh(LoadMesh);	
	}

	SetBaseStaticMeshComponent(healthkit_mesh);
	SetSoundTouchSound(LoadObject<USoundBase>(nullptr, TEXT("/Game/Sound/ActorSound/Cue/Pickup_Health_Cue")));
}
#define HEALTH_AMOUNTH = 25;

void Aitem_healthkit::BeginPlay()
{
	Super::BeginPlay();
}


void Aitem_healthkit::Use(AActor* pCharacterUse)
{
	Super::Use(pCharacterUse);

	HealthComponent = Cast<UHealthComponent>(pCharacterUse->GetComponentByClass(UHealthComponent::StaticClass()));

	if (HealthComponent != nullptr)
	{
		if (HealthComponent->GetPlayerHealth() < HealthComponent->GetPlayerMaxHealth())
		{
			HealthComponent->RestoreHealth(10);
			SetUse(true);
			
			if (GetSoundTouch() != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, GetSoundTouch(), GetActorLocation());

			}
		}
	}
	
}
