// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_WEAPON/weapon_smg1.h"

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
	FTransform Transform = smg1_mesh->GetSocketTransform("ShellSpawn", RTS_World);
	FVector LocationSpawn = Transform.GetLocation();
	FRotator SpawnRotation = Transform.GetRotation().Rotator();
	
	TObjectPtr<AShell> Shell = GetWorld()->SpawnActor<AShell>(shelldrops, Transform.GetLocation(), FRotator::ZeroRotator, ActorSpawnParameters);
	if (Shell)
	{
		//FVector ForwardVector = LocationSpawn.ForwardVector;
		//Shell->GetMeshBullet()->AddImpulse(ForwardVector* 200);
	}
}


	

