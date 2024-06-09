// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "Property/Poolable.h"
#include "bullet_decal.generated.h"
class UDecalComponent;
/* This class Only spawn for object pool and weapon trace this game */
UCLASS()
class JOBSGAME_API Abullet_decal : public ADecalActor, public IPoolable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> material_bulletdecal;
	
public:
	// Sets default values for this actor's properties
	Abullet_decal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Interface call
	virtual void Activate() override;
	virtual void Deactivate() override; 

public:


	
};
