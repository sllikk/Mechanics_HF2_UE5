// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "decal_object_pool.generated.h"

UCLASS()
class Adecal_object_pool : public ADecalActor
{
	GENERATED_BODY()


public:

	Adecal_object_pool();
	
public:

	UFUNCTION(CallInEditor, Category="DecalPool")
	ADecalActor* GetDecalObject();

	UFUNCTION(CallInEditor, Category="DecalPool")
	void ReleaseDecalObject(ADecalActor* DecalActor);

	void InitializeDecalPool(TSubclassOf<ADecalActor> Object, int32 SizePool);
	
private:


	UPROPERTY()
	TSubclassOf<AActor> PooledObjectClass; // Class of the object that will be stored in the pool

	UPROPERTY()
	int32 PoolSize; // Size Pool

	UPROPERTY()
	TArray<ADecalActor*> Pool; // Array Object Pool

	UPROPERTY()
	TArray<ADecalActor*> AvailableObjects; // Array available Object Pool 
};
