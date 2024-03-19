// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/BatteryKit.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PlayerComponent/CostumeComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogBatteryKit);

ABatteryKit::ABatteryKit()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Amounth = 15.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Game/WorldActors/RestoreKits/BatteryKit_Box"));
	if (StaticMesh.Succeeded())
	{

		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BatteryKit"));
		MeshComponent->SetStaticMesh(StaticMesh.Object);
		MeshComponent->SetSimulatePhysics(true);
		MeshComponent->SetMassScale("BaatteryKit", 35.0f);
		MeshComponent->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
		SetRootComponent(MeshComponent);	
	
		CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
		CollisionSphere->InitSphereRadius(110.0f);
		CollisionSphere->SetCollisionProfileName(TEXT("OverllupAll"));
		CollisionSphere->SetupAttachment(MeshComponent);
	
	}
	else
	{
		UE_LOG(LogBatteryKit, Warning, TEXT("Eror find object!!!!"));
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> Sound(TEXT("/Game/Sound/ActorSound/Cue/Pickup_Battery_Cue"));
	if (Sound.Succeeded())
	{
		SoundPickup = Sound.Object;
	}
	else
	{
		UE_LOG(LogBatteryKit, Warning, TEXT("Eror find sound!!!!"));
	}

}


void ABatteryKit::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABatteryKit::NotifyActorBeginOverlap(AActor* OtherActor)
{
	CostumeComponent = Cast<UCostumeComponent>(OtherActor->GetComponentByClass(UCostumeComponent::StaticClass()));
	
		if (CostumeComponent != nullptr)
		{
			if (CostumeComponent->m_CurrentChargerCostume < CostumeComponent->m_MaxChargerCostume)
			{
				CostumeComponent->RestoreCharger(m_Amounth);
				
				if (SoundPickup != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, SoundPickup, GetActorLocation());
				}
				
				Destroy();
			}
			
			
		}
}



