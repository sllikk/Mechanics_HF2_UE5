// Fill out your copyright notice in the Description page of Project Settings.

#include "Shared/TestCheats.h"

#include "WorldActors/BatteryKit.h"
#include "WorldActors/FlameBarrel.h"
#include "WorldActors/HealthKit.h"
#include "WorldActors/supply_crate.h"

#if PLATFORM_WINDOWS

struct FSpawnCheat
{
	TMap<const FString, const TSubclassOf<AActor>> SPAWNNER; 

	FSpawnCheat()
	{
		SPAWNNER.Add(TEXT("flamebarrel"), AFlameBarrel::StaticClass());
		SPAWNNER.Add(TEXT("healthkit"), AHealthKit::StaticClass());
		SPAWNNER.Add(TEXT("batterykit"), ABatteryKit::StaticClass());
		SPAWNNER.Add(TEXT("supply_crate"), Asupply_crate::StaticClass());
	}
};


UTestCheats::UTestCheats()
{

}

void UTestCheats::ForceGarbageCollection()
{
	GEngine->ForceGarbageCollection(true);
}


void UTestCheats::SpawnInteractObject(const FString& ObjectName) const
{
	FSpawnCheat SpawnCheat;
	if (SpawnCheat.SPAWNNER.Contains(ObjectName))
	{
		if (GEngine != nullptr)
		{
			UWorld* World = GetWorld();
			if (World != nullptr)
			{
				const TSubclassOf<AActor>* SpawnActor = SpawnCheat.SPAWNNER.Find(ObjectName);
				const APlayerController* PlayerController = World->GetFirstPlayerController();
				if (PlayerController != nullptr)
				{
					const FVector& Location = PlayerController->GetPawn()->GetActorLocation() + PlayerController->GetPawn()->GetActorForwardVector() * 300.0f;
					const FRotator& Rotation = FRotator::ZeroRotator;
				
					FActorSpawnParameters SpawnParams;
					SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					World->SpawnActor<AActor>(*SpawnActor, Location, Rotation, SpawnParams);
				}
			}
		}
	}
}


void UTestCheats::spawn_props(const FString& SpawnerClass) const
{
	SpawnInteractObject(SpawnerClass);
}


void UTestCheats::spawn_npc(const FString& SpawnerClass) const
{
	SpawnInteractObject(SpawnerClass);
}


#endif
