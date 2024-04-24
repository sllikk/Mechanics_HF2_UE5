// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Resourse.generated.h"

USTRUCT()
struct FResourceLoad
{
	GENERATED_BODY()

	UPROPERTY()	
	FString ResourcePath;
	UPROPERTY()
	TObjectPtr<UObject> LoadedResource;

	FResourceLoad(){}
	FResourceLoad(const FString& resource_path, UObject* loaded_resource)
		: ResourcePath(resource_path), LoadedResource(loaded_resource){}
	
};

UCLASS()
class JOBSGAME_API UResourse : public UObject
{
	GENERATED_BODY()
};
