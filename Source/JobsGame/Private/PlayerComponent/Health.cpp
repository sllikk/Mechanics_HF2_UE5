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

	// Default Property
	m_flMaxHealth = 100;
	m_flHealth = m_flMaxHealth;

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
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (GEngine != nullptr)
	{
		FString strHealth = FString::Printf(TEXT("Health: %2.f"), GetHealth());
		GEngine->AddOnScreenDebugMessage(1, 120, FColor::White, strHealth);
	}
	
}


void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (GetMaxHealth() < 0 || m_blsDead)
	{
		return;
	}
	// Custom Damage	
	const UCustomDamage* CustomDamage = Cast<const UCustomDamage>(DamageType);
	if ( CustomDamage != nullptr )
	{
		const EDamageType& DamageData =	CustomDamage->GetCurrentDamageType();
		const FDamageTypeData& DamageTypeData = CustomDamage->GetDamageTypeData();
		static float ModeferDamage = Damage * DamageTypeData.DamageMultiplayer;

		m_flHealth = FMath::Clamp(GetHealth() - ModeferDamage, 0.0f, GetMaxHealth());

		UE_LOG(LogActor, Warning, TEXT("Damage: %2.f, TYPE: %s"), ModeferDamage,  *UEnum::GetValueAsString(DamageData))
		
		if (GetHealth() <= 0)
		{
		
		}
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("Error"))
	}
}


bool UHealthComponent::RestoreHealth(float HealthAmount)
{
	m_flHealth += HealthAmount;
	m_flHealth = FMath::Min(m_flHealth, m_flMaxHealth);

	return GetHealth() <= GetMaxHealth();
	
}

	





