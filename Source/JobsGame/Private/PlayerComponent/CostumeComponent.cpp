// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerComponent/CostumeComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogCostumeComponent);

UCostumeComponent::UCostumeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_MaxChargerCostume = 100;
	m_CurrentChargerCostume = m_MaxChargerCostume;

	
}


void UCostumeComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UCostumeComponent::TakeDamage);
	}
}


void UCostumeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GEngine)
	{
		FString Costume = FString::Printf(TEXT("Costume: %2.f"), m_CurrentChargerCostume);
		GEngine->AddOnScreenDebugMessage(2, 20.0f, FColor::Yellow, Costume);
	}

}


void UCostumeComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (m_MaxChargerCostume < 0 || m_blsDischargerCostume)
	{
		return;
	}

	m_CurrentChargerCostume = FMath::Clamp(m_CurrentChargerCostume - Damage, 0.0f, m_MaxChargerCostume);

	if (m_CurrentChargerCostume <= 0)
	{
		CostumeDischarged();
	}

}


bool UCostumeComponent::RestoreCharger(float Amounth)
{
	m_CurrentChargerCostume += Amounth;
	m_CurrentChargerCostume = FMath::Min(m_CurrentChargerCostume, m_MaxChargerCostume);

	return m_CurrentChargerCostume < m_MaxChargerCostume;

}

void UCostumeComponent::CostumeDischarged()
{
	m_blsDischargerCostume = true;
	
	UE_LOG(LogCostumeComponent, Warning, TEXT("COSTUME_DISCHARGERED!!!!"));

}


