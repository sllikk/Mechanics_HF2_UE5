// Fill out your copyright notice in the Description page of Project Settings.

#include "Shared/TestCheats.h"

#include "WorldActors/BatteryKit.h"
#include "WorldActors/FlameBarrel.h"
#include "WorldActors/HealthKit.h"

void UTestCheats::ForceGarbageCollection()
{
	GEngine->ForceGarbageCollection(true);
}


// DEFAULT SPAWN FUNC
void UTestCheats::SpawnInteractObject(const TSubclassOf<AActor> ActorClass)
{
	if (GEngine != nullptr)
	{
		UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);
		if (World)
		{
			const APlayerController* PlayerController = World->GetFirstPlayerController();
			if (PlayerController)
			{
				const FVector& Location = PlayerController->GetPawn()->GetActorLocation() + PlayerController->GetPawn()->GetActorForwardVector() * 150.0f;
				const FRotator& Rotation = FRotator::ZeroRotator;
				
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				World->SpawnActor<AActor>(ActorClass, Location, Rotation, SpawnParams);
			}
		}
	}
}

void UTestCheats::flamebarrel_spawn()
{
	SpawnInteractObject(AFlameBarrel::StaticClass());
}


void UTestCheats::healthkit_spawn()
{
	SpawnInteractObject(AHealthKit::StaticClass());
}

void UTestCheats::suitkit_spawn()
{
	SpawnInteractObject(ABatteryKit::StaticClass());
}


