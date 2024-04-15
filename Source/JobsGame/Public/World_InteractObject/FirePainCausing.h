// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirePainCausing.generated.h"
class UBoxComponent;
class UParticleSystem;
class UCustomDamage;

DECLARE_LOG_CATEGORY_EXTERN(FirePainCausing, Log, All);

UCLASS()
class JOBSGAME_API AFirePainCausing : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "BoxComponent", meta=(AllowPrivateAccess = "true")) 
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Particles", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> FireParticles;
	
public:	
	
	AFirePainCausing();

protected:

	virtual void BeginPlay() override;

public:	

	UFUNCTION(Blueprintable)
	void OnDetectionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	 virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	UPROPERTY(EditAnywhere, Category = "DamageType")
	TObjectPtr<UCustomDamage> CustomDamage;
	
};

