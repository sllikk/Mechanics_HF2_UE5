// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerComponent/Suit.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogCostumeComponent);

USuitComponent::USuitComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	m_MaxChargerCostume = 100;
	m_CurrentChargerCostume = m_MaxChargerCostume;

	
	
}


void USuitComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &USuitComponent::TakeDamage);
	}
}


void USuitComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GEngine)
	{
		FString strSuit = FString::Printf(TEXT("Suit: %2.f"), m_CurrentChargerCostume);	
		GEngine->AddOnScreenDebugMessage(2, 120, FColor::White, strSuit);
	}
	
}


void USuitComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
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


bool USuitComponent::RestoreCharger(float Amounth)
{
	m_CurrentChargerCostume += Amounth;
	m_CurrentChargerCostume = FMath::Min(m_CurrentChargerCostume, m_MaxChargerCostume);

	return m_CurrentChargerCostume < m_MaxChargerCostume;

}

void USuitComponent::CostumeDischarged()
{
	m_blsDischargerCostume = true;
	
	UE_LOG(LogCostumeComponent, Warning, TEXT("COSTUME_DISCHARGERED!!!!"));

}


