// Fill out your copyright notice in the Description page of Project Settings.

#include "World_InteractObject/PainVolume.h"
#include "Engine/DamageEvents.h"

APainVolume::APainVolume(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

	bPainCausing = true;
	DamageType = UDamageType::StaticClass();
	DamagePerSec = 1.0f;
	bEntryPain = true;
	PainInterval = 1.0f;
	
}


void APainVolume::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BACKUP_bPainCausing	= bPainCausing;

}

void APainVolume::ActorEnteredVolume(AActor* Other)
{
	Super::ActorEnteredVolume(Other);

	if ( bPainCausing && bEntryPain && Other->CanBeDamaged() )
	{
		CausePainTo(Other);
	}

	// Start timer if none is active
	if (!GetWorldTimerManager().IsTimerActive(TimerHandle_PainTimer))
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PainTimer, this, &APainCausingVolume::PainTimer, PainInterval, true);
	}

}


void APainVolume::CausePainTo(AActor* Other)
{
	Super::CausePainTo(Other);

	if (DamagePerSec > 0.f)
	{
		TSubclassOf<UDamageType> DmgTypeClass = DamageType ? *DamageType : UDamageType::StaticClass();
		Other->TakeDamage(DamagePerSec*PainInterval, FDamageEvent(DmgTypeClass), DamageInstigator, this);
	}
	
}

void APainVolume::PainTimer()
{
	Super::PainTimer();

	if (bPainCausing)
	{
		TSet<AActor*> TouchingActors;
		GetOverlappingActors(TouchingActors);

		for (AActor* const A : TouchingActors)
		{
			if (IsValid(A) && A->CanBeDamaged() && A->GetPhysicsVolume() == this)
			{
				CausePainTo(A);
			}
		}

		// Stop timer if nothing is overlapping us
		if (TouchingActors.Num() == 0)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle_PainTimer);
		}
	}

}


void APainVolume::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(TimerHandle_PainTimer);
}
