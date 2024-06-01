// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_WEAPON/weapon_smg1.h"

#include "Components/ArrowComponent.h"
#include "Shared/Shell.h"

enum State
{
	AUTO_FIRE = 1 << 0,   //0001 
	SINGLE_FIRE = 1 << 1, // 0010
	ALT_FIRE = 1 << 2,   // 00100
};


Aweapon_smg1::Aweapon_smg1()
{
	smg1_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = smg1_mesh;
	
	smg1_mesh->SetCollisionProfileName("Weapons");
	smg1_mesh->SetWorldRotation(FRotator(0, 80, 0));

	SpawnShellArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	SpawnShellArrow->SetupAttachment(smg1_mesh);
	
	SetSkeletalMesh(smg1_mesh);
	LoadSkeletalMesh("/Game/Weapon/Smg/Smg1");
	SetBulletSpread(5.0f);
	SetSocetName("Muzzle");
	SetMaxShootDistance(6000);
	SetMaxAmmo(45);
	SetInvAmmo(225);
	SetReloadTime(1.0f);
	SetImpulseImpact(1000);
	SetAttackRate(0.1);

		
}


void Aweapon_smg1::BeginPlay()
{
	Super::BeginPlay();

	SetFireSound(LoadObject<USoundBase>(nullptr, TEXT("/Game/Sound/Weapon/Cue/smg_fire_Cue")));

}


void Aweapon_smg1::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void Aweapon_smg1::PrimaryAttack()
{
	Super::PrimaryAttack();
	
	SpawnShell();
}


void Aweapon_smg1::Interact(AActor* Actor)
{
	Super::Interact(Actor);
}

void Aweapon_smg1::ApplyDamage(float Damage, FVector HitLocation)
{
	Super::ApplyDamage(Damage, HitLocation);
	
}

void Aweapon_smg1::PhysicsTraceLogic(const FHitResult& HitResult)
{
	Super::PhysicsTraceLogic(HitResult);
}

void Aweapon_smg1::StartAttack()
{
	Super::StartAttack();
	
		
}

void Aweapon_smg1::StopAttack()
{
	Super::StopAttack();
}

void Aweapon_smg1::SpawnShell() const
{
	FActorSpawnParameters ActorSpawnParameters;
	FVector LocationSpawn = SpawnShellArrow->GetComponentLocation();

	TObjectPtr<AShell> Shell = GetWorld()->SpawnActor<AShell>(shelldrops,  LocationSpawn, FRotator::ZeroRotator , ActorSpawnParameters);
	if (Shell != nullptr)
	{
		 FVector ForwardVector = SpawnShellArrow->GetForwardVector();

		Shell->GetMeshBullet()->AddImpulse(ForwardVector* 500, NAME_Actor, true);

	}
}


	

