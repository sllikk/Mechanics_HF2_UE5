// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/BatteryKit.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PlayerComponent/Suit.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogBatteryKit);

ABatteryKit::ABatteryKit()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Amounth = 15.0f;

	// Load Mesh in Battery Kit
	FSoftObjectPath MeshAsset(TEXT("/Game/WorldActors/RestoreKits/SuitKit/suit_kit"));
	UStaticMesh* StaticMesh = nullptr;

	if (MeshAsset.IsValid())
	{
		StaticMesh = Cast<UStaticMesh>(MeshAsset.TryLoad());
	}
	if (StaticMesh != nullptr)
	{
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BatteryKit"));
		MeshComponent->SetStaticMesh(StaticMesh);
		MeshComponent->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
		SetRootComponent(MeshComponent);	
		
		CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
		CollisionSphere->InitSphereRadius(1200.0f);
		CollisionSphere->SetCollisionProfileName(TEXT("OverllupAll"));
		CollisionSphere->SetupAttachment(MeshComponent);
	}
	else
	{
		UE_LOG(LogBatteryKit, Warning, TEXT("Eror find object: %s"), *MeshAsset.ToString());
	}

	// Load PickUp Sound
	FSoftObjectPath SoundFinder(TEXT("/Game/Sound/ActorSound/Cue/Pickup_Battery_Cue"));
	USoundBase* SoundBase = nullptr;

	if (SoundFinder.IsValid())
	{
		SoundBase = Cast<USoundBase>(SoundFinder.TryLoad());
	}
	if (SoundBase != nullptr)
	{
		SoundPickup = SoundBase;
	}
	else
	{
		UE_LOG(LogBatteryKit, Warning, TEXT("Eror find sound!!!!"));
	}

}


void ABatteryKit::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent->SetSimulatePhysics(true);
	
}


void ABatteryKit::NotifyActorBeginOverlap(AActor* OtherActor)
{
	SuitComponent = Cast<USuitComponent>(OtherActor->GetComponentByClass(USuitComponent::StaticClass()));
	
		if (SuitComponent != nullptr)
		{
			if (SuitComponent->m_CurrentChargerCostume < SuitComponent->m_MaxChargerCostume)
			{
				SuitComponent->RestoreCharger(m_Amounth);
				
				if (SoundPickup != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, SoundPickup, GetActorLocation());
					Destroy();
				}
			}
		}
	}



