// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Logging/LogMacros.h"
#include "HopperMine.generated.h"
class UStaticMeshComponent;
class USoundBase;
class USphereComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogLoadResourceMine, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogHopper, Log, All);

UCLASS(Config = Game)
class JOBSGAME_API AHopperMine : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> HopperMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "SphereComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> DetectedSphere;

	
	UPROPERTY(EditDefaultsOnly, Category = "SphereComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> ActiveSphere;

public:	
	
	AHopperMine();

protected:
	
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
public:	
	
	virtual void Tick(float DeltaTime) override;
	
private:

	void ActivateMine();
	
	
};

struct FLoadResource
{
	FString ResourcePath;
	UObject* LoadedResource;
};

