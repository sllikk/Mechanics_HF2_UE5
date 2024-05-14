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

