// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerCameraManager.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ABasePlayerCameraManager::ABasePlayerCameraManager()
{
	bls_dead = false;
	flDeathAnimTime = 2.0f;
}

void ABasePlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	if (bls_dead)
	{
		flCurrentTimeTick += DeltaTime; 

		float t = FMath::Clamp(flCurrentTimeTick / flDeathAnimTime, 0.0f, 1.0f);
		FVector NewLocation = FMath::Lerp(InitialCameraLocation, InitialCameraLocation + FVector(0, 0, -200.0f), t);

		// Обновляем позицию камеры
		FTransform NewTransform = GetTransform();
		NewTransform.SetLocation(NewLocation);
		SetActorTransform(NewTransform);
		
		if (flCurrentTimeTick >= flDeathAnimTime)
		{
			bls_dead = false;
		}
	}

	
}


void ABasePlayerCameraManager::PlayDeathCameraAnim()
{
	bls_dead = true;
	flCurrentTimeTick = 0.0f;
	InitialCameraLocation = GetCameraLocation();
}
