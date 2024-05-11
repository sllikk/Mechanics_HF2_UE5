// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "shotgun.generated.h"
class UStaticMeshComponent;
class USkeletalMeshComponent;
class USoundBase;
class UParticleSystemComponent;

UCLASS(Blueprintable)
class JOBSGAME_API Ashotgun : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Blueprintable,Category="GunMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> ShotgunSkeletal;

	//UPROPERTY(EditAnywhere, Category="Shell", meta=(AllowPrivateAccess = "true"))
	//TObjectPtr<UStaticMeshComponent> Shells;
	
	UPROPERTY(EditAnywhere, Category="MuzzleFlesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> MuzzleFlesh;
	
public:
	// Sets default values for this actor's properties
	Ashotgun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	void Fire();
};
