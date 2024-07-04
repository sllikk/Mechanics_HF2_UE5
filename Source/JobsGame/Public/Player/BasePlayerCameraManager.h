// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "Camera/PlayerCameraManager.h"
#include "BasePlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class JOBSGAME_API ABasePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:

	ABasePlayerCameraManager();

protected:

	virtual void UpdateCamera(float DeltaTime) override;
	UPROPERTY()
	UCameraComponent* CameraComponent;
	
public:

	void PlayDeathCameraAnim();
	
private:

	bool bls_dead;
	float flCurrentTimeTick;
	float flDeathAnimTime;
	
	FVector InitialCameraLocation;
	FVector InitialCameraRotation;
	
};
