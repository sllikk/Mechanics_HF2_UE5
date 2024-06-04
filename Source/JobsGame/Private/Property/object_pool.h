// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "object_pool.generated.h"

UCLASS()
class Aobject_pool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aobject_pool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(CallInEditor, Category="ObjectPool")
	AActor* GetObject(); 

	UFUNCTION(CallInEditor, Category = "Object Pool")
	void ReleaseObject(AActor* Object);

	void InitializePool(TSubclassOf<AActor> Object, int32 SizePool);

private:

	UPROPERTY()
	TSubclassOf<AActor> PooledObjectClass; // Class of the object that will be stored in the pool

	UPROPERTY()
	int32 PoolSize; // Size Pool

	//UPROPERTY()
	//TArray<AActor*> Pool; // Array Object Pool

	UPROPERTY()
	TArray<AActor*> AvailableObjects; // Array available Object Pool 
	
};
