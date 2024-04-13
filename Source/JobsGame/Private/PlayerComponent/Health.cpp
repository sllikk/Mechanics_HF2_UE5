// Fill out your copyright notice in the Description page of Project Settings.
\
#include "PlayerComponent/Health.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyCharacter.h"

DEFINE_LOG_CATEGORY(LogHeathComponent);
DEFINE_LOG_CATEGORY(LogHeathResource);

UHealthComponent::UHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	
	m_MaxHealth = 100;
	m_CurrentHealth = m_MaxHealth;


	// Load Resource sound for health
	TArray<FResourceLoad> ResourceToLoad = {

	FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/Dead-Sound_Cue"),nullptr},	
	FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/deactivated_Cue"),nullptr},	
	FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/heat_damage_Cue"),nullptr},	
	FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/major_fracture_Cue"),nullptr},	
	FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/minor_fracture_Cue"),nullptr},	
	FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/morphine_shot_Cue"),nullptr},	
	FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/near_death_Cue"),nullptr},	
	FResourceLoad{TEXT("/Game/Sound/ActorSound/Cue/no_pulce_Cue"),nullptr},	
	};
	for (FResourceLoad& Resource : ResourceToLoad)
	{
		Resource.LoadResource = LoadObject<UObject>(nullptr, *Resource.ResourcePath);
		if (Resource.LoadResource)
		{
			UE_LOG(LogHeathResource, Warning, TEXT("Load: %s"), *Resource.ResourcePath)
		}
		else
		{
			UE_LOG(LogHeathResource, Warning, TEXT("Error Loaded: %s"), *Resource.ResourcePath)
		}
	}
	for (const FResourceLoad& Resource : ResourceToLoad)
	{
		USoundBase* LoadSound = Cast<USoundBase>(Resource.LoadResource);

		if (LoadSound != nullptr)
		{
			HealthSound.Add(LoadSound);
		}	
	}
}



void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
	UE_LOG(LogHeathComponent, Warning, TEXT("LOAD!!!!!!!!!!"))
	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}


void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	// Base Take damage
	if (m_MaxHealth < 0 || m_blsDead)
	{
		return;
	}

	m_CurrentHealth = FMath::Clamp(m_CurrentHealth - Damage, 0.0f, m_MaxHealth);

	if (m_CurrentHealth <= 0)
	{
		IsDead();
	}

	





}

void UHealthComponent::SoundActiviti(float Damage)
{
}


void UHealthComponent::IsDead()
{
	m_blsDead = true;
	
	UE_LOG(LogHeathComponent, Warning, TEXT("DEAD!!!!!!!"))
	
}


bool UHealthComponent::RestoreHealth(float HealthAmount)
{
	m_CurrentHealth += HealthAmount;
	m_CurrentHealth = FMath::Min(m_CurrentHealth, m_MaxHealth);

	return m_CurrentHealth < m_MaxHealth;
	
}
