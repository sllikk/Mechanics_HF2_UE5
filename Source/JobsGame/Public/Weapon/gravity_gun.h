// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gravity_gun.generated.h"
class UStaticMeshComponent;
class UPhysicsHandleComponent;
class USoundBase;

UCLASS()
class JOBSGAME_API Agravity_gun : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Blueprintable, Category = "WeaponMesh", meta=(AllowPrivateAccess = "true"))		
	TObjectPtr<UStaticMeshComponent> GravityGunMesh;

	UPROPERTY(EditAnywhere, Blueprintable, Category = "MechanicsPhysics", meta=(AllowPrivateAccess = "true"))		
	TObjectPtr<UPhysicsHandleComponent> MechanicsPhysics;
	
public:	

	Agravity_gun();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
