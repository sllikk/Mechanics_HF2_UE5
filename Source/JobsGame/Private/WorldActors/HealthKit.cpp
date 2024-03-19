// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/HealthKit.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PlayerComponent/HealthComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY(LogHealthKit);

AHealthKit::AHealthKit()
{

	PrimaryActorTick.bCanEverTick = false;

	m_Amounth = 25.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAssets(TEXT("/Game/WorldActors/RestoreKits/HealthKit_Box"));	
	if (MeshAssets.Succeeded())
	{
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealthKit"));
		MeshComponent->SetStaticMesh(MeshAssets.Object);
		MeshComponent->SetSimulatePhysics(true);
		MeshComponent->SetMassScale("HealthKit", 35.0f);
		MeshComponent->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
		SetRootComponent(MeshComponent);
		
		CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
		CollisionSphere->InitSphereRadius(110.0f);
		CollisionSphere->SetCollisionProfileName(TEXT("OverllupAll"));
		CollisionSphere->SetupAttachment(MeshComponent);
		
	}
	else
	{
		UE_LOG(LogHealthKit, Warning, TEXT("Eror find object!!!!"));
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> Sound(TEXT("/Game/Sound/ActorSound/Cue/Pickup_Health_Cue"));
	if (Sound.Succeeded())
	{
		
		SoundPickup = Sound.Object;
	}
	else
	{
		UE_LOG(LogHealthKit, Warning, TEXT("Eror find sound!!!!"));

	}

}


void AHealthKit::BeginPlay()
{
	Super::BeginPlay();
	

}

void AHealthKit::NotifyActorBeginOverlap(AActor* OtherActor)
{
	HealthComponent = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));

	if (HealthComponent != nullptr)
	{
		if (HealthComponent->m_CurrentHealth < HealthComponent->m_MaxHealth)
		{
			HealthComponent->RestoreHealth(m_Amounth);
			
			if (SoundPickup != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SoundPickup, GetActorLocation());
			}
		
			Destroy();
		}

	}

}








