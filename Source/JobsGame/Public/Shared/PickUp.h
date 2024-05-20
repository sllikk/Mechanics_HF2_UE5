// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shared/grab_sphere.h"
#include "PickUp.generated.h"
class Ugravity_gun;
class Ugrab_sphere;

UCLASS()
class JOBSGAME_API APickUp : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Blueprintable , BlueprintReadWrite ,Category="Gravity_gun", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<Ugravity_gun> Gravity_Gun;

	UPROPERTY(EditAnywhere, Blueprintable , BlueprintReadWrite ,Category="Gravity_gun", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<Ugrab_sphere> Grab_Sphere;
	
public:
	// Sets default values for this actor's properties
	APickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
