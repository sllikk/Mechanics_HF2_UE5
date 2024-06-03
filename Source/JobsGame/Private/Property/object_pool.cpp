// Fill out your copyright notice in the Description page of Project Settings.


#include "Property/object_pool.h"

// Sets default values
Aobject_pool::Aobject_pool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PoolSize = 10;
}

// Called when the game starts or when spawned
void Aobject_pool::BeginPlay()
{
	Super::BeginPlay();

}


AActor* Aobject_pool::GetObject()
{
	if (AvailableObjects.Num() > 0)
	{
		AActor* Object = AvailableObjects.Pop();		
		Object->SetActorHiddenInGame(false);
		return Object;
	}
	return nullptr;
}

void Aobject_pool::ReleaseObject(AActor* Obect)
{
	if (Obect != nullptr)
	{
		Obect->SetActorHiddenInGame(true);	
		AvailableObjects.Add(Obect);
		
	}
}

void Aobject_pool::InitializePool(TSubclassOf<AActor> Object, int32 SizePool)
{
	PoolSize = SizePool;
	PooledObjectClass = Object;


	if (PooledObjectClass != nullptr)
	{
		for (int32 i = 0; i < PoolSize; ++i)
		{
			AActor* NewObject = GetWorld()->SpawnActor<AActor>(PooledObjectClass);
			if (NewObject != nullptr)
			{
				NewObject->SetActorHiddenInGame(true);
				Pool.Add(NewObject);
				AvailableObjects.Add(NewObject);
				UE_LOG(LogTemp, Warning, TEXT("Object added to pool: %s"), *NewObject->GetName());
			}
		}
	}
	
}


