// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "Containers/Map.h"
#include "TestCheats.generated.h"

USTRUCT(BlueprintType)
struct FDebugInfoHitActor
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category="Debug")
	FString Name;

	UPROPERTY(BlueprintReadWrite, Category="Debug")
	FString Model;
	
	//UPROPERTY(BlueprintReadWrite, Category="Debug")
	//float Health;

	UPROPERTY(BlueprintReadWrite, Category="Debug")
	FVector Location;
	
};

UCLASS()
class JOBSGAME_API UTestCheats : public UCheatManager
{
	GENERATED_BODY()
	
public:

	UTestCheats();
	
	// Useful for identifying hanging pointers that could cause a crash when
	UFUNCTION( exec )
	void ForceGarbageCollection();
	UFUNCTION( exec )
	void spawn_props(const FString& SpawnerClass) const;
	UFUNCTION( exec )
	void spawn_npc(const FString& SpawnerClass) const;

private:
	
	FORCEINLINE void SpawnInteractObject(const FString& ObjectName) const;
	
};
