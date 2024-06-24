// Fill out your copyright notice in the Description page of Project Settings.

#include "Property/ImpactEffectHandler.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AImpactEffectHandler::AImpactEffectHandler()
{
	SoundBases.Reserve(12);
	ParticleSystems.Reserve(12);
}


// Called when the game starts or when spawned
void AImpactEffectHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

void AImpactEffectHandler::EffectForSurface(const FHitResult& HitResult)
{
	auto phys_material = HitResult.PhysMaterial.Get();
	if(!phys_material) return;
	EPhysicalSurface surface_type = UPhysicalMaterial::DetermineSurfaceType(phys_material);

	surface(surface_type, HitResult);
}


void AImpactEffectHandler::surface(EPhysicalSurface surface_type, const FHitResult& HitResult)
{
	if (SoundBases.Num() > 0 && ParticleSystems.Num() > 0)
	{
		switch (surface_type)
		{
		case SurfaceType1:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[0], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[0], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
		case SurfaceType2:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[1], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[1], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
		case SurfaceType3:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[2], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[2], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
		case SurfaceType4:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[3], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[3], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
		case SurfaceType5:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[4], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[4], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
		case SurfaceType6:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[5], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[5], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
		case SurfaceType7:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[6], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[6], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
		case SurfaceType8:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[7], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[7], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
		case SurfaceType9:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[8], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[8], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
		case SurfaceType10:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[9], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[9], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
		case SurfaceType11:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[10], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[10], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
		case SurfaceType12:
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBases[11], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystems[11], HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			break;
			
		default:
		case SurfaceType_Default:
			break;
		}
	}
}

