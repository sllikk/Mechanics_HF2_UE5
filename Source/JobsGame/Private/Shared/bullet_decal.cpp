// Fill out your copyright notice in the Description page of Project Settings.


#include "bullet_decal.h"
#include "Components/DecalComponent.h"


// Sets default values
Abullet_decal::Abullet_decal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	/* Bullet hole material load*/
	const FSoftObjectPath FindMaterial(TEXT("/Game/Weapon/m_bullethole")); 
	TObjectPtr<UMaterial> LoadMaterial = nullptr;
	if (FindMaterial.IsValid())
	{
		LoadMaterial = Cast<UMaterial>(FindMaterial.TryLoad());
	}
	if (LoadMaterial != nullptr)
	{
		material_bulletdecal = LoadMaterial;
	}
	else
	{
		UE_LOG(LogLoad, Error, TEXT("Error Loac %s"), *FindMaterial.ToString())
	}

	SetDecalMaterial(material_bulletdecal);
	GetDecal()->SetWorldScale3D(FVector(0.010f, 0.010f, 0.010f));

}

// Called when the game starts or when spawned
void Abullet_decal::BeginPlay()
{
	Super::BeginPlay();
	
}

////////////////////////////////////////////////////////////////////////////////////////////////
// object pool interface
void Abullet_decal::Activate()
{
	this->SetActorHiddenInGame(false);
}

void Abullet_decal::Deactivate()
{
	this->SetActorHiddenInGame(true);
}


