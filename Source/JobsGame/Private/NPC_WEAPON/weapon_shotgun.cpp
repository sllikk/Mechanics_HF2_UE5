// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_WEAPON/weapon_shotgun.h"

Aweapon_shotgun::Aweapon_shotgun()
{ 
	shotgun_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("shotgun_mesh"));
	RootComponent = shotgun_mesh;

	const FSoftObjectPath findshotgun(TEXT("/Game/Weapon/ShotGun/spas_mesh"));
	static TObjectPtr<USkeletalMesh> LoadMesh = nullptr;
	if (findshotgun.IsValid())
	{
		LoadMesh = Cast<USkeletalMesh>(findshotgun.TryLoad());
	}
	if (LoadMesh != nullptr)
	{
		shotgun_mesh->SetSkeletalMesh(LoadMesh);
	}

	SetSkeletalMesh(shotgun_mesh);
	SetBulletSpread(6.0f);
	SetSocetName("Muzzle");
	SetMaxShootDistance(3000);
	SetMaxAmmo(6);
	SetInvAmmo(32);
	SetReloadTime(1.2f);
	SetPhysicsImpulse(500.0f);
	SetAttackRate(1);
}

void Aweapon_shotgun::BeginPlay()
{
	Super::BeginPlay();
	
	// Load Sound for this weapon
	SetFireSound(LoadObject<USoundBase>(nullptr, TEXT("")));
	SetReloadSound(LoadObject<USoundBase>(nullptr, TEXT("")));
}

void Aweapon_shotgun::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void Aweapon_shotgun::PrimaryAttack()
{
	Super::PrimaryAttack();
}

void Aweapon_shotgun::StartAttack()
{
	for (uint8 i = 0; i < 5; ++i)
	{
		Super::StartAttack();
	}
}

void Aweapon_shotgun::StopAttack()
{
	Super::StopAttack();
}
