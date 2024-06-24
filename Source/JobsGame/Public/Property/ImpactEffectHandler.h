// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shared/Resourse.h"
#include "ImpactEffectHandler.generated.h"
class USoundBase;
class UParticleSystem;

UCLASS()
class JOBSGAME_API AImpactEffectHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImpactEffectHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

	void EffectForSurface(const FHitResult& HitResult);
	void surface(EPhysicalSurface surface, const FHitResult& HitResult);
	
private:

	UPROPERTY(EditAnywhere, Category="effect")
	TArray<USoundBase*> SoundBases ;

	UPROPERTY(EditAnywhere, Category="Effect")
	TArray<UParticleSystem*> ParticleSystems;	


};
