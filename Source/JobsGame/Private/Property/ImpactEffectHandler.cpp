// Fill out your copyright notice in the Description page of Project Settings.


#include "Property/ImpactEffectHandler.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AImpactEffectHandler::AImpactEffectHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TArray<FResourceLoad> SoundLoads = {

	FResourceLoad{ TEXT(""), nullptr },	
	FResourceLoad{ TEXT(""), nullptr },	
	FResourceLoad{ TEXT(""), nullptr },	
	FResourceLoad{ TEXT(""), nullptr },	
	FResourceLoad{ TEXT(""), nullptr },	
	FResourceLoad{ TEXT(""), nullptr },	
	FResourceLoad{ TEXT(""), nullptr },	
	FResourceLoad{ TEXT(""), nullptr },	
	FResourceLoad{ TEXT(""), nullptr },	
		
	};
	
	for( FResourceLoad ResourceLoad : SoundLoads )
	{
		ResourceLoad.LoadedResource = LoadObject<UObject>(nullptr, *ResourceLoad.ResourcePath);

		if (!ResourceLoad.LoadedResource)
		{
			UE_LOG(LogLoad, Error, TEXT("Error load: %s"), *ResourceLoad.ResourcePath)
		}
	}

	for ( const FResourceLoad& LoadResource : SoundLoads )
	{
		USoundBase* SoundBase = Cast<USoundBase>(LoadResource.LoadedResource);
		if (SoundBase != nullptr)
		{
			LoadSound.Add(SoundBase);
		}
	}
	
	SurfaceImpactEffects.Emplace(EPhysicalSurfaceType::DEFAULT, {});
	SurfaceImpactEffects.Emplace(EPhysicalSurfaceType::METAL, {});
	SurfaceImpactEffects.Emplace(EPhysicalSurfaceType::WOOD, {});
	SurfaceImpactEffects.Emplace(EPhysicalSurfaceType::PAPER, {});
	SurfaceImpactEffects.Emplace(EPhysicalSurfaceType::PLASTIC, {});
	SurfaceImpactEffects.Emplace(EPhysicalSurfaceType::ASPHALT, {});
	SurfaceImpactEffects.Emplace(EPhysicalSurfaceType::SAND, {});
	SurfaceImpactEffects.Emplace(EPhysicalSurfaceType::GLASS, {});
	SurfaceImpactEffects.Emplace(EPhysicalSurfaceType::GROUND, {});
	
}

// Called when the game starts or when spawned
void AImpactEffectHandler::BeginPlay()
{
	Super::BeginPlay();


	
}

// PlaySound and Effect for hit 
void AImpactEffectHandler::PlayImpactEffects(EPhysicalSurfaceType SurfaceType, const FVector& ImpactPoint, const FVector& ImpactNormal)
{
	const FSurfaceImpactEffects* ImpactEffects = SurfaceImpactEffects.Find(SurfaceType);
	if (ImpactEffects != nullptr)
	{
		if (ImpactEffects->ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ImpactEffects->ImpactSound, ImpactPoint);
		}

		if (ImpactEffects->ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffects->ImpactEffect, ImpactPoint, ImpactNormal.Rotation());
		}
	}
}

