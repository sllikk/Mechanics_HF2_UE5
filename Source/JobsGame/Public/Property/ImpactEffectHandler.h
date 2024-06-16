// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shared/Resourse.h"
#include "ImpactEffectHandler.generated.h"
class USoundBase;
class UParticleSystemComponent;

UCLASS(BlueprintType)
class JOBSGAME_API AImpactEffectHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImpactEffectHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TMap<EPhysicalSurfaceType, FSurfaceImpactEffects> SurfaceImpactEffects;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TArray<USoundBase*> LoadSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TArray<UParticleSystemComponent*> LoadParticles;
	
	
public:	

	void PlayImpactEffects(EPhysicalSurfaceType SurfaceType, const FVector& ImpactPoint, const FVector& ImpactNormal);
	
	
};
