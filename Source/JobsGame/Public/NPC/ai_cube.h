// Fill out your copyright notice in the Description page of Project Settings.

//																ONLY TEST ACTOR DON'T PACK GAME

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Property/debug_entity.h"	
#include "ai_cube.generated.h"
class UStaticMeshComponent;
class UAIPerceptionStimuliSourceComponent; 
class UAIPerceptionComponent;
class Udebug_entity;

UENUM()
enum ECubeState
{
	IDLE,
	CHASE,
	ATTACK,
	
};

UCLASS(Blueprintable)
class JOBSGAME_API Aai_cube : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category="Ai", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionStimuliSourceComponent> PerceptionStimuliSourceComponent;
	
public:
	// Sets default values for this actor's properties
	Aai_cube(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void  OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
public:

	UPROPERTY()
	TObjectPtr<Udebug_entity> pdebug_entity;

	ECubeState State;
	FString Debug;
};	

