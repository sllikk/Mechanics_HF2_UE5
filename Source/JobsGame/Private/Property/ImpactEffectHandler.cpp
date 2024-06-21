// Fill out your copyright notice in the Description page of Project Settings.


#include "Property/ImpactEffectHandler.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AImpactEffectHandler::AImpactEffectHandler()
{

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

	auto surface_type = UPhysicalMaterial::DetermineSurfaceType(phys_material);
	switch (surface_type)
	{
	case SurfaceType1:
		if (Concrete)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Concrete, HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
		}
		break;
	case SurfaceType2:
		break;
	case SurfaceType3:
		break;
	case SurfaceType4:
		break;
	case SurfaceType5:
		break;
	case SurfaceType6:
		break;
	case SurfaceType7:
		break;
	case SurfaceType8:
		break;
	case SurfaceType9:
		break;
	case SurfaceType10:
		break;
	case SurfaceType11:
		break;
	case SurfaceType12:
		break;
	case SurfaceType13:
		break;
	case SurfaceType14:
		break;
	case SurfaceType15:
		break;
	case SurfaceType16:
		break;
	case SurfaceType17:
		break;
	case SurfaceType18:
		break;
	case SurfaceType19:
		break;
	case SurfaceType20:
		break;
	case SurfaceType21:
		break;
	case SurfaceType22:
		break;
	case SurfaceType23:
		break;
	case SurfaceType24:
		break;
	case SurfaceType25:
		break;
	case SurfaceType26:
		break;
	case SurfaceType27:
		break;
	case SurfaceType28:
		break;
	case SurfaceType29:
		break;
	case SurfaceType30:
		break;
	case SurfaceType31:
		break;
	case SurfaceType32:
		break;
	case SurfaceType33:
		break;
	case SurfaceType34:
		break;
	case SurfaceType35:
		break;
	case SurfaceType36:
		break;
	case SurfaceType37:
		break;
	case SurfaceType38:
		break;
	case SurfaceType39:
		break;
	case SurfaceType40:
		break;
	case SurfaceType41:
		break;
	case SurfaceType42:
		break;
	case SurfaceType43:
		break;
	case SurfaceType44:
		break;
	case SurfaceType45:
		break;
	case SurfaceType46:
		break;
	case SurfaceType47:
		break;
	case SurfaceType48:
		break;
	case SurfaceType49:
		break;
	case SurfaceType50:
		break;
	case SurfaceType51:
		break;
	case SurfaceType52:
		break;
	case SurfaceType53:
		break;
	case SurfaceType54:
		break;
	case SurfaceType55:
		break;
	case SurfaceType56:
		break;
	case SurfaceType57:
		break;
	case SurfaceType58:
		break;
	case SurfaceType59:
		break;
	case SurfaceType60:
		break;
	case SurfaceType61:
		break;
	case SurfaceType62:
		break;
	case SurfaceType_Max:
		break;
	default:
	case SurfaceType_Default:
		break;
	}
}



