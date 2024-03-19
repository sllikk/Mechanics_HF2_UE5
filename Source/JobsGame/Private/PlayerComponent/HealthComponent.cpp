// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerComponent/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogHeathComponent);

UHealthComponent::UHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	m_MaxHealth = 100.0f;
	m_CurrentHealth = m_MaxHealth;

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

	if (GEngine)
	{
		FString CurrentHealth = FString::Printf(TEXT("Health: %.2f"), m_CurrentHealth);
		GEngine->AddOnScreenDebugMessage(1, 20.0f, FColor::Yellow, CurrentHealth);
	}

}


void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
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


void UHealthComponent::IsDead()
{
	m_blsDead = true;

	if (DeadSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeadSound, GetOwner()->GetActorLocation());
		UE_LOG(LogHeathComponent, Warning, TEXT("DEAD!!!!!!!"))
	}

}


bool UHealthComponent::RestoreHealth(float HealthAmount)
{
	m_CurrentHealth += HealthAmount;
	m_CurrentHealth = FMath::Min(m_CurrentHealth, m_MaxHealth);

	return m_CurrentHealth < m_MaxHealth;

}