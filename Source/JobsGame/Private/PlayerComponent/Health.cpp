// Fill out your copyright notice in the Description page of Project Settings.
\
#include "PlayerComponent/Health.h"
#include " Property/CustomDamage.h"

class UCustomDamage;
DEFINE_LOG_CATEGORY(LogHeathComponent);
DEFINE_LOG_CATEGORY(LogHeathResource);

UHealthComponent::UHealthComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
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
		if (!Resource.LoadResource)
		{
			UE_LOG(LogHeathResource, Warning, TEXT("Error Load: %s"), *Resource.ResourcePath)	
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
		//Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
	UE_LOG(LogHeathComponent, Warning, TEXT("LOAD!!!!!!!!!!"))
	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}


void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	const UCustomDamage* CustomDamage = Cast<const UCustomDamage>(DamageType);

	if (CustomDamage)
	{
		FDamageTypeData DamageTypeData = CustomDamage->GetDamageTypeData();

		switch (CustomDamage->DamageType)
		{
		case EDamageType::DMG_FIRE:
			FireDamage(Damage, DamageTypeData);
			break;
		case EDamageType::DMG_ELECTRIC:
			ElectricalDamage(Damage, DamageTypeData);
			break;
		case EDamageType::DMG_FALL:
			FallDamage(Damage, DamageTypeData);
			break;
		case EDamageType::DMG_PHYSICS:
			PhysicsDamage(Damage, DamageTypeData);
			break;
		case EDamageType::DMG_EXPLOSION:
			ExplosionDamage(Damage, DamageTypeData);
			break;
		default:
			break;
	
		}
	}

	if (m_MaxHealth < 0 || m_blsDead)
	{
		return;
	}
	
	if (m_CurrentHealth <= 0)
	{
		IsDead();
	}
	
}


void UHealthComponent::IsDead()
{
	m_blsDead = true;
	
	UE_LOG(LogHeathComponent, Warning, TEXT("DEAD!!!!!!!"))
	
}


void UHealthComponent::FireDamage(float Damage, const FDamageTypeData& DamageTypeData)
{
	 float FinalDamage = Damage * DamageTypeData.DamageMultiplayer;
	m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
	UE_LOG(LogHeathComponent, Warning, TEXT("Fire" ))		
}

void UHealthComponent::ElectricalDamage(float Damage, const FDamageTypeData& DamageTypeData)
{
	 float FinalDamage = Damage * DamageTypeData.DamageMultiplayer;
	m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
	UE_LOG(LogHeathComponent, Warning, TEXT("Electrical" ))		

}

void UHealthComponent::FallDamage(float Damage, const FDamageTypeData& DamageTypeData)
{
	 float FinalDamage = Damage * DamageTypeData.DamageMultiplayer;
	m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
	UE_LOG(LogHeathComponent, Warning, TEXT("Fall" ))		

}


void UHealthComponent::PhysicsDamage(float Damage, const FDamageTypeData& DamageTypeData)
{
	 float FinalDamage = Damage * DamageTypeData.DamageMultiplayer;
	m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
	UE_LOG(LogHeathComponent, Warning, TEXT("Physics" ))		
	
}


void UHealthComponent::ExplosionDamage(float Damage, const FDamageTypeData& DamageTypeData)
{
	 float FinalDamage = Damage * DamageTypeData.DamageMultiplayer;
	m_CurrentHealth = FMath::Clamp(m_CurrentHealth - Damage, 0.0f, m_MaxHealth);
	UE_LOG(LogHeathComponent, Warning, TEXT("Explosion"))		
	

}


bool UHealthComponent::RestoreHealth(float HealthAmount)
{
	m_CurrentHealth += HealthAmount;
	m_CurrentHealth = FMath::Min(m_CurrentHealth, m_MaxHealth);

	return m_CurrentHealth < m_MaxHealth;
	
}
