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

// Effect for hit surface
USTRUCT(BlueprintType)
struct FSurfaceImpactEffects
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UParticleSystem> ImpactEffect;

};


// Surface type
UENUM(BlueprintType, meta=(ScriptName = "CustomSurfaceType"))
enum class EPhysicalSurfaceType : uint8
{
	DEFAULT				UMETA(DisplayName = "default surface"),
	CONCRETE			UMETA(DisplayName = "concrete surface"),
	WOOD				UMETA(DisplayName = "wood surface"),
	METAL				UMETA(DisplayName = "metal surface"),
	GLASS				UMETA(DisplayName = "glass surface"),
	PAPER				UMETA(DisplayName = "paper surface"),
	ASPHALT				UMETA(DisplayName = "asphalt surface"),
	GROUND				UMETA(DisplayName = "ground surface"),
	PLASTIC				UMETA(DisplayName = "plastic surface"),
	SAND				UMETA(DisplayName = "sand surface"),
};


/*
USTRUCT()
struct FDebugProps
{
	GENERATED_BODY()
	
	
	UPROPERTY(EditAnywhere, Category="Debug")
	FString& Name;

	UPROPERTY(EditAnywhere, Category="Debug")
	FString& Model;

	UPROPERTY(EditAnywhere, Category="Debug")
	FString& AnimationSequence;

	UPROPERTY(EditAnywhere, Category="Debug")
	float& Health;

	UPROPERTY(EditAnywhere, Category="Debug")
	FVector& Location;

	UPROPERTY(EditAnywhere, Category="Debug")
	FVector& Stress;
	
};
*/

UCLASS()
class JOBSGAME_API UResourse : public UObject
{
	GENERATED_BODY()
};
