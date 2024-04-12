// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Logging/LogMacros.h"
#include "BatteryKit.generated.h"
class UStaticMeshComponent;
class USuitComponent;
class USphereComponent;
class USoundBase;

DECLARE_LOG_CATEGORY_EXTERN(LogBatteryKit, Log, All);

UCLASS()

class JOBSGAME_API ABatteryKit : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> CollisionSphere;

public:	

	ABatteryKit();

protected:
	
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> SoundPickup;

private:

	TObjectPtr<USuitComponent> SuitComponent;
	float m_Amounth;

};
