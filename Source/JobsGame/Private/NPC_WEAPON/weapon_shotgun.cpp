// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_WEAPON/weapon_shotgun.h"


// Sets default values
Aweapon_shotgun::Aweapon_shotgun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	shotgun_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));	
	RootComponent = shotgun_mesh;
	shotgun_mesh->SetCollisionProfileName("Weapons");

	SetSkeletalMesh(shotgun_mesh);	
	SetMaxShootDistance(1000);
	SetSocetName("Muzzle");
	LoadSkeletalMesh("/Game/Weapon/ShotGun/Spas12");

	SetMaxAmmo(6);
	SetInvAmmo(30);
	SetReloadTime(1.0f);
}

// Called when the game starts or when spawned
void Aweapon_shotgun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void Aweapon_shotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Aweapon_shotgun::Fire()
{
	Super::Fire();

	
}

