// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerComponent/Health.h"
#include "Property/CustomDamage.h"
#include "Shared/Resourse.h"

DEFINE_LOG_CATEGORY(LogHeathComponent);
DEFINE_LOG_CATEGORY(LogHeathResource);

UHealthComponent::UHealthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), m_blsDead(false)
{
	PrimaryComponentTick.bCanEverTick = true;

	// Load Resource sound for health
	TArray<FResourceLoad> ResourceToLoad = {
		FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/Dead-Sound_Cue"), nullptr},
		FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/deactivated_Cue"), nullptr},
		FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/heat_damage_Cue"), nullptr},
		FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/major_fracture_Cue"), nullptr},
		FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/minor_fracture_Cue"), nullptr},
		FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/morphine_shot_Cue"), nullptr},
		FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/near_death_Cue"), nullptr},
		FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/no_pulce_Cue"), nullptr},
	};
	for (FResourceLoad& Resource : ResourceToLoad)
	{
		Resource.LoadedResource = LoadObject<UObject>(nullptr, *Resource.ResourcePath);
		if (!Resource.LoadedResource)
		{
			UE_LOG(LogHeathResource, Warning, TEXT("Error Load: %s"), *Resource.ResourcePath)
		}
	}

	for (const FResourceLoad& Resource : ResourceToLoad)
	{
		USoundBase* LoadSound = Cast<USoundBase>(Resource.LoadedResource);

		if (LoadSound != nullptr)
		{
			HealthSound.Add(LoadSound);
		}
	}

	imaxhealth = 100;
	icurrent_health = imaxhealth;
	
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
}



bool UHealthComponent::RestoreHealth(int32 HealthAmount)
{
	icurrent_health += HealthAmount;
	icurrent_health = FMath::Min(icurrent_health, imaxhealth);

	return GetPlayerHealth() <= GetPlayerMaxHealth();
	
}

	





