// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_WEAPON/weapon_smg1.h"

#include "Components/ArrowComponent.h"

Aweapon_smg1::Aweapon_smg1()
{
	smg1_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("smg1_mesh"));
	RootComponent = smg1_mesh;

	SpawnShellArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("drop_shell"));
	SpawnShellArrow->SetupAttachment(smg1_mesh);
	
	const FSoftObjectPath find_mesh(TEXT("/Game/Weapon/Smg/smg_mesh"));
	static TObjectPtr<USkeletalMesh> LoadMesh = nullptr;
	if (find_mesh.IsValid())
	{
		LoadMesh = Cast<USkeletalMesh>(find_mesh.TryLoad());
	}

	if (LoadMesh != nullptr)
	{
		smg1_mesh->SetSkeletalMesh(LoadMesh);
	}

	SetSkeletalMesh(smg1_mesh);
	SetBulletSpread(5.0f);
	SetSocetName("Muzzle");
	SetMaxShootDistance(6000);
	SetMaxAmmo(45);
	SetInvAmmo(225);
	SetReloadTime(1.2f);
	SetPhysicsImpulse(250.0f);
	SetAttackRate(0.1);
}

void Aweapon_smg1::BeginPlay()
{
	Super::BeginPlay();

	// Load Sound for this weapon
	SetFireSound(LoadObject<USoundBase>(nullptr, TEXT("/Game/Sound/Weapon/Cue/smg_fire_Cue")));
	SetReloadSound(LoadObject<USoundBase>(nullptr, TEXT("/Game/Sound/Weapon/Cue/smg_reload_Cue")));

}

void Aweapon_smg1::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Debug();
}

void Aweapon_smg1::PrimaryAttack()
{
	Super::PrimaryAttack();
	
}

void Aweapon_smg1::StartAttack()
{
	Super::StartAttack();
}

void Aweapon_smg1::StopAttack()
{
	Super::StopAttack();
}

