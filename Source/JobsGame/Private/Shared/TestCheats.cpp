// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/TestCheats.h"

#include "WorldActors/FlameBarrel.h"

void UTestCheats::ForceGarbageCollection()
{
	GEngine->ForceGarbageCollection(true);
}

void UTestCheats::Spawn_FlameBarrel()
{
	if (GEngine != nullptr)
	{
		UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);
		if (World)
		{
			APlayerController* PlayerController = World->GetFirstPlayerController();
			if (PlayerController)
			{
				FVector Location = PlayerController->GetPawn()->GetActorLocation() + PlayerController->GetPawn()->GetActorForwardVector() * 100.0f;
				FRotator Rotation = FRotator::ZeroRotator;
				
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				World->SpawnActor<AFlameBarrel>(AFlameBarrel::StaticClass(), Location, Rotation, SpawnParams);
			}
		}
	}

}


