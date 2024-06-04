// Fill out your copyright notice in the Description page of Project Settings.


#include "Property/decal_object_pool.h"

Adecal_object_pool::Adecal_object_pool()
{
	PoolSize = 15;
	Pool.Reserve(PoolSize);
	AvailableObjects.Reserve(PoolSize);
	
}

void Adecal_object_pool::InitializeDecalPool(TSubclassOf<ADecalActor> Object, int32 SizePool)
{
	PooledObjectClass = Object;
	PoolSize = SizePool;

	if (PooledObjectClass != nullptr)
	{
		for (int32 i = 0; i < PoolSize; ++i)
		{
			ADecalActor* NewObject = GetWorld()->SpawnActor<ADecalActor>(PooledObjectClass);
			if (NewObject != nullptr)
			{
				NewObject->SetActorHiddenInGame(true);
				AvailableObjects.Add(NewObject);
				Pool.Add(NewObject);
			}
		}
		
	}
}


ADecalActor* Adecal_object_pool::GetDecalObject()
{
	if (AvailableObjects.Num() > 0)
	{
		ADecalActor* DecalActor = AvailableObjects.Pop();
		DecalActor->SetActorHiddenInGame(false);
		return DecalActor;
	}
	return nullptr;
}

void Adecal_object_pool::ReleaseDecalObject(ADecalActor* DecalActor)
{
	if (DecalActor != nullptr)
	{
		DecalActor->SetActorHiddenInGame(true);
		AvailableObjects.Add(DecalActor);
		
	}
	
}

