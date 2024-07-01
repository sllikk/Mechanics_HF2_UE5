// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/item_healthkit.h"

#include "Components/BoxComponent.h"
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

	SetSoundTouchSound(LoadObject<USoundBase>(nullptr, TEXT("/Game/Sound/ActorSound/Cue/Pickup_Health_Cue")));
	
	SetRadiusSphere(3800.0f);
	SetBaseStaticMeshComponent(healthkit_mesh);
	GetTriggerCollision()->SetupAttachment(healthkit_mesh);
	GetTriggerCollision()->SetWorldLocation(FVector(0, 0, 500));
	GetTriggerCollision()->InitSphereRadius(GetSphereRadius());
	SetMassObj(12.0f);	

}

void Aitem_healthkit::BeginPlay()
{
	Super::BeginPlay();

	
}


void Aitem_healthkit::OnTouch(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnTouch(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}


constexpr uint8 UE_HEALTH_AMOUNTH =  25;

void Aitem_healthkit::Use(AActor* pCharacterUse)
{
	Super::Use(pCharacterUse);

	ptrPlayer = Cast<AMyCharacter>(pCharacterUse);
	if (ptrPlayer != nullptr)
	{
		if (ptrPlayer->GetPlayerHealth() < ptrPlayer->GetPlayerMaxHealth())
		{
			ptrPlayer->RestoreHealth(UE_HEALTH_AMOUNTH);
			if (GetSoundTouch() != nullptr)
			{
				SetUse(true);
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), GetSoundTouch(), GetActorLocation());
			}
		}
	}
	
}
