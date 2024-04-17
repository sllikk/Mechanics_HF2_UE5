// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerComponent/Health.h"

#include "Property/CustomDamage.h"

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
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}


void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (const UCustomDamage* CustomDamage = Cast<const UCustomDamage>(DamageType))
	{
		const FDamageTypeData& DamageTypeData = CustomDamage->GetDamageTypeData();

		switch (CustomDamage->DamageType)
		{
		case EDamageType::DMG_EXPLOSION:
			ExplosionDamage(Damage, DamageTypeData);
			break;
		case EDamageType::DMG_FIRE:
		FireDamage(Damage, DamageTypeData);
			break;	
		case EDamageType::DMG_ELECTRIC:
			ElectricDamage(Damage, DamageTypeData);
			break;
		case EDamageType::DMG_FALL:
			FallDamage(Damage, DamageTypeData);
			break;
		case EDamageType::DMG_DROWN:
			DrownDamage(Damage, DamageTypeData);
			break;
		case EDamageType::DMG_PHYSICS:
			PhysicsDamage(Damage, DamageTypeData);
			break;
		case EDamageType::DMG_WEAPON:
			WeaponDamage(Damage, DamageTypeData);
			break;
	
		default:
		break;
		}	
	}
	else
	{
		UE_LOG(LogHeathComponent, Warning, TEXT("Error Casting"));
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
	
	void UHealthComponent::ExplosionDamage(float Damage, const FDamageTypeData& DamageTypeData)
	{
		float FinalDamage = DamageTypeData.DamageMultiplayer;
		m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
		UE_LOG(LogHeathComponent, Warning, TEXT("ExplosionDamage"));		
	}

	void UHealthComponent::FireDamage(float Damage, const FDamageTypeData& DamageTypeData)
	{
		float FinalDamage = DamageTypeData.DamageMultiplayer;
		m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
		UE_LOG(LogHeathComponent, Warning, TEXT("FireDamage"));		
	}


	void UHealthComponent::ElectricDamage(float Damage, const FDamageTypeData& DamageTypeData)
	{
		float FinalDamage = DamageTypeData.DamageMultiplayer;
		m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
		UE_LOG(LogHeathComponent, Warning, TEXT("ElectricDamage"));		
	}


	void UHealthComponent::FallDamage(float Damage, const FDamageTypeData& DamageTypeData)
	{
		float FinalDamage =DamageTypeData.DamageMultiplayer;
		m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
		UE_LOG(LogHeathComponent, Warning, TEXT("FallDamage"));		
	}


	void UHealthComponent::DrownDamage(float Damage, const FDamageTypeData& DamageTypeData)
	{
		float FinalDamage = DamageTypeData.DamageMultiplayer;
		m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
		UE_LOG(LogHeathComponent, Warning, TEXT("DrownDamage"));		
	}
	
	
	void UHealthComponent::PhysicsDamage(float Damage, const FDamageTypeData& DamageTypeData)
	{
		float FinalDamage = Damage* DamageTypeData.DamageMultiplayer;
		m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
		UE_LOG(LogHeathComponent, Warning, TEXT("PhysicsDamage"));		
	}
	
	void UHealthComponent::WeaponDamage(float Damage, const FDamageTypeData& DamageTypeData)
	{
		float FinalDamage = Damage* DamageTypeData.DamageMultiplayer;
		m_CurrentHealth = FMath::Clamp(m_CurrentHealth - FinalDamage, 0.0f, m_MaxHealth);
		UE_LOG(LogHeathComponent, Warning, TEXT("WeaponDamage"));		

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
