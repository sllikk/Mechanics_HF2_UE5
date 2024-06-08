// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Property/Poolable.h"
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

	template<typename T>
	FORCEINLINE T* GetObject(); 

	UFUNCTION(CallInEditor, Category = "Object Pool")
	void ReleaseObject(AActor* Object);
	UFUNCTION()
	void InitializePool(TSubclassOf<AActor> Object, int32 SizePool);

private:

	UPROPERTY()
	TSubclassOf<AActor> PooledObjectClass; // Class of the object that will be stored in the pool

	UPROPERTY()
	int32 PoolSize; // Size Pool

	UPROPERTY()
	TArray<AActor*> AvailableObjects; // Array available Object Pool 
	
};

template <typename T>
T* Aobject_pool::GetObject()  
{
	
	if (AvailableObjects.Num() > 0)
	{
		AActor* Object = AvailableObjects.Pop();

		if (IPoolable* PoolableObject = Cast<IPoolable>(Object))
		{
			PoolableObject->Activate();
		}

		return Cast<T>(Object);
	}

	return nullptr;
}
