// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Logging/LogMacros.h"
#include "HealthKit.generated.h"
class UStaticMeshComponent;
class UHealthComponent;
class USphereComponent;
class USoundBase;

DECLARE_LOG_CATEGORY_EXTERN(LogHealthKit, Log, All);

UCLASS()

class JOBSGAME_API AHealthKit : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAcces = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Collision", meta = (AllowPrivateAcces = "true"))
	TObjectPtr<USphereComponent> CollisionSphere;


public:	
	
	AHealthKit();

protected:
	
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


public:

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	TObjectPtr<USoundBase> SoundPickup;

private:

	TObjectPtr<UHealthComponent> HealthComponent;

	float m_Amounth;

};
