// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Debug_Object.generated.h"
class UStaticMeshComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogDebug_Object, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogDebug_ResourceObject, Log, All);

UCLASS()
class JOBSGAME_API ADebug_Object : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "MeshPrototype", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PrototypeMeshComponent;


	
public:	
	
	ADebug_Object();

protected:
	
	virtual void BeginPlay() override;
	
public:	
	
	virtual void Tick(float DeltaTime) override;
	
public:

	// debug weight and position 
	void DebugPrototype();
	
private:

	void GetWeight();
	
};
