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
				FVector Location; 
				FRotator Rotation; 
				PlayerController->GetPlayerViewPoint(Location, Rotation);

				FVector const& End = Location + (Rotation.Vector() * 500.0f);

				FHitResult HitResult;
				FCollisionQueryParams QueryParams;
				QueryParams.AddIgnoredActor(PlayerController->GetPawn());

				if (PlayerController->GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECC_Visibility, QueryParams))
				{
					DrawDebugSphere(GetWorld(), HitResult.Location, 15, 32, FColor::Cyan, false, 2.0f);

					const FRotator& SpawnRotator = FRotator::ZeroRotator;

					FActorSpawnParameters SpawnParams;
					SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					World->SpawnActor<AActor>(ActorClass, HitResult.Location, Rotation, SpawnParams);	
					
				}
				else
				{
					// Место занято, возможно, выводим сообщение или логируем
					UE_LOG(LogTemp, Warning, TEXT("Cannot spawn, location is blocked"));
				}
				
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


