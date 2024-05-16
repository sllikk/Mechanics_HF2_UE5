// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Shared/TestCheats.h"

DEFINE_LOG_CATEGORY(BASE_CONTROLLER)

ABasePlayerController::ABasePlayerController()
{
	// Cheat Class 
	CheatClass = UTestCheats::StaticClass();
}

void ABasePlayerController::BeginPlay()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMapping, 0);
		
	}

	UE_LOG(BASE_CONTROLLER, Warning, TEXT("BeginPlay!!!!"))

}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}


void ABasePlayerController::ent_text()
{
	if(GEngine != nullptr)
	{
		const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController != nullptr)
		{
			FVector Location;
			FRotator Rotation;
			PlayerController->GetPlayerViewPoint(Location, Rotation);

			const FVector& End = Location + (Rotation.Vector() * 200);

			FHitResult HitResult;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(PlayerController->GetPawn());

			if (GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECC_Visibility, Params))
			{
				AActor* DEBUG_INFO = HitResult.GetActor();

				if (DEBUG_INFO != nullptr)
				{	
					FDebugInfoHitActor InfoHitActor;
					
					// Заполняем данные
					InfoHitActor.Name = *DEBUG_INFO->GetName();
					InfoHitActor.Model = *DEBUG_INFO->GetClass()->GetName();
					InfoHitActor.Location = DEBUG_INFO->GetActorLocation();
					
					// Debug	
					FVector DebugLocaton = DEBUG_INFO->GetActorLocation(); 
					DrawDebugString(GetWorld(), DebugLocaton, InfoHitActor.Name, nullptr, FColor::Silver, -1, false, 0.8f);
					DrawDebugString(GetWorld(), DebugLocaton, InfoHitActor.Location.ToString(), nullptr, FColor::Silver, -1, false, 0.9f);
					
				}
			}
		}
	}
}
