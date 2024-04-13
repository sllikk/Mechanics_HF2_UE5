// Fill out your copyright notice in the Description page of Project Settings.

#include "World_InteractObject/PainVolume.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Property/CustomDamageType.h"

class UCustomDamageType;
DEFINE_LOG_CATEGORY(LogPainCausing)

APainVolume::APainVolume(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
	bPainCausing = true;
	DamageType = UDamageType::StaticClass();
	DamagePerSec = 1.0f;
	bEntryPain = true;
	PainInterval = 1.0f;

	const FSoftObjectPath FindParticle(TEXT("/Game/VFX/Particles/Fire/P_Fire_Big"));	
	UParticleSystem* ParticleSystem = nullptr;
	
	if (FindParticle.IsValid())
	{
		ParticleSystem = Cast<UParticleSystem>(FindParticle.TryLoad());
	}
	if (ParticleSystem != nullptr)
	{
		FireParticle = ParticleSystem;
	}
	else
	{
		UE_LOG(LogPainCausing, Warning, TEXT("Error find: %s"), *FindParticle.ToString())
	}
	
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

void APainVolume::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<FLoadSound> ResourceToLoad = {
	FLoadSound{TEXT("/Game/Sound/Sound_InteractObj/Cue/Pain_Causing_Cue"), nullptr},
	FLoadSound{TEXT("/Game/Sound/Sound_InteractObj/Cue/fire_loop_Cue"), nullptr}
	};
	for (FLoadSound& Resource : ResourceToLoad)
	{
		Resource.LoadResource = LoadObject<UObject>(nullptr, *Resource.ResourcePath);
		if (Resource.LoadResource)
		{
			UE_LOG(LogPainCausing, Warning, TEXT("Load: %s"), *Resource.ResourcePath);
		}
		else
		{
			UE_LOG(LogPainCausing, Warning, TEXT("Error load: %s"), *Resource.ResourcePath);
		}
	}
	for (const FLoadSound& Resource : ResourceToLoad)
	{
		USoundBase* SoundBase = Cast<USoundBase>(Resource.LoadResource);

		if (SoundBase != nullptr)
		{
			FireSound.Add(SoundBase);
		}
	}
	
		
	if (FireParticle != nullptr && FireSound[1] != nullptr)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, FireSound[1], GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(this, FireParticle, GetActorLocation());
	}
	
}


void APainVolume::CausePainTo(AActor* Other)
{
	Super::CausePainTo(Other);

	if (DamagePerSec > 0.f)
	{
		UCustomDamageType* CustomDamage = NewObject<UCustomDamageType>();
		if (CustomDamage)
		{
			CustomDamage->DamageType = EDamageType::DMG_FIRE;
			FDamageTypeData DamageTypeData = CustomDamage->GetDamageTypeData();
			UGameplayStatics::ApplyDamage(Other, DamagePerSec * PainInterval, DamageInstigator, this, CustomDamage->GetClass());
			UE_LOG(LogCustomDamage, Warning, TEXT("Type %d with multiplier %f"), static_cast<int32>(CustomDamage->DamageType), DamageTypeData.DamageMultiplayer);

			
		}
		else
		{
			UE_LOG(LogCustomDamage, Error, TEXT("Failed to create CustomDamage object"));
		}


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
				if (FireSound[0] != nullptr)
				{
					UGameplayStatics::SpawnSoundAtLocation(this, FireSound[0], GetActorLocation());
					CausePainTo(A);
				}
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
