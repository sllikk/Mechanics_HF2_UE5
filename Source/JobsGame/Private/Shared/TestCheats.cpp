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
void UTestCheats::SpawnInteractObject(const TSubclassOf<AActor> ActorClass) const
{
	if (GEngine != nullptr)
	{
		UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);
		if (World)
		{
			const APlayerController* PlayerController = World->GetFirstPlayerController();
			if (PlayerController)
			{
				const FVector& Location = PlayerController->GetPawn()->GetActorLocation() + PlayerController->GetPawn()->GetActorForwardVector() * 300.0f;
				const FRotator& Rotation = FRotator::ZeroRotator;
				
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				World->SpawnActor<AActor>(ActorClass, Location, Rotation, SpawnParams);
			}
		}
	}
}


void UTestCheats::spawn_flamebarrel()
{
	SpawnInteractObject(AFlameBarrel::StaticClass());
}


void UTestCheats::spawn_healthkit()
{
	SpawnInteractObject(AHealthKit::StaticClass());
}


void UTestCheats::spawn_batterykit()
{
	SpawnInteractObject(ABatteryKit::StaticClass());
}


