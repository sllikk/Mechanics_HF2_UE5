// Fill out your copyright notice in the Description page of Project Settings.

#include "Shared/TestCheats.h"

#include "WorldActors/BatteryKit.h"
#include "WorldActors/FlameBarrel.h"
#include "WorldActors/HealthKit.h"

// Struct Spawn Object for World
struct FSpawnClass
{
	TMap<const FString, const TSubclassOf<AActor>> SPAWNER;

	FSpawnClass()
	{ 
		SPAWNER.Add(TEXT("flamebarrel"), AFlameBarrel::StaticClass());
		SPAWNER.Add(TEXT("healthkit"), AHealthKit::StaticClass());
		SPAWNER.Add(TEXT("batterykit"), ABatteryKit::StaticClass());
	}
	
};


UTestCheats::UTestCheats()
{
	
}

void UTestCheats::ForceGarbageCollection()
{
	GEngine->ForceGarbageCollection(true);
}

void UTestCheats::spawn_props(const FString& SpawnerClass) const
{
	SpawnInteractObject(SpawnerClass);
}

void UTestCheats::spawn_npc(const FString& SpawnerClass) const
{
	SpawnInteractObject(SpawnerClass);
}

// DEFAULT SPAWN FUNC
void UTestCheats::SpawnInteractObject(const FString& ObjectName) const
{
	static FSpawnClass Cheats;

	if (Cheats.SPAWNER.Contains(ObjectName))
	{
		if (GEngine != nullptr)
		{
			const TSubclassOf<AActor>* ObjectClass = Cheats.SPAWNER.Find(ObjectName);
			if (ObjectClass != nullptr)
			{
				UWorld* World = GetWorld();
				if (World != nullptr)
				{
					const APlayerController* PlayerController = World->GetFirstPlayerController();
					if (PlayerController != nullptr)
					{
						const FVector& Location = PlayerController->GetPawn()->GetActorLocation() + PlayerController->GetPawn()->GetActorForwardVector() * 300.0f;
						const FRotator& Rotation = FRotator::ZeroRotator;
				
						FActorSpawnParameters SpawnParams;
						SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
						World->SpawnActor<AActor>(*ObjectClass, Location, Rotation, SpawnParams);
					}
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Object class not found for %s"), *ObjectName);
	}
}



