// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perception/AIPerceptionComponent.h"
#include "ai_cube.generated.h"
class UStaticMeshComponent;
class UAIPerceptionStimuliSourceComponent; 
class UAIPerceptionComponent;

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

public:

	
};

