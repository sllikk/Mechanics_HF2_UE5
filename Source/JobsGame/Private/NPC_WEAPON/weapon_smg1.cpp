// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_WEAPON/weapon_smg1.h"
#include "Components/ArrowComponent.h"
#include "Property/object_pool.h"
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
	SetReloadTime(1.2f);
	SetPhysicsImpulse(350.0f);
	SetAttackRate(0.1);



}


void Aweapon_smg1::BeginPlay()
{
	Super::BeginPlay();

	SetFireSound(LoadObject<USoundBase>(nullptr, TEXT("/Game/Sound/Weapon/Cue/smg_fire_Cue")));
	SetReloadSound(LoadObject<USoundBase>(nullptr, TEXT("/Game/Sound/Weapon/Cue/smg_reload_Cue")));
	
}


void Aweapon_smg1::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void Aweapon_smg1::PrimaryAttack()
{
		Super::PrimaryAttack();
}


void Aweapon_smg1::Interact(AActor* Actor)
{
	Super::Interact(Actor);
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

void Aweapon_smg1::ShellDrop()
{
	Super::ShellDrop();

	//if (GetShellPool() != nullptr)
	{
		/*
			TObjectPtr<AShell> SpawnShell = Cast<AShell>(GetShellPool()->GetObject());
	
			if (SpawnShell != nullptr)
			{
				SpawnShell->SetActorLocation(SpawnShellArrow->GetComponentLocation());	
				SpawnShell->SetActorRotation(FRotator::ZeroRotator);
				PoolArray.Add(SpawnShell);
	
				if (SpawnShellArrow != nullptr)
				{
					const FVector& ForwardVector = SpawnShellArrow->GetForwardVector();
					SpawnShell->GetMeshBullet()->AddImpulse(ForwardVector * 500, NAME_None, true);
				}
			}
		}
		*/
	}
}

void Aweapon_smg1::ObjectPoolRelease()
{
	Super::ObjectPoolRelease();

		if (PoolArray.Num() > 0)
		{
			for (int32 i = 0; i < PoolArray.Num(); ++i)
			{
			//	GetShellPool()->ReleaseObject(PoolArray[i]);
			}
			PoolArray.Empty();
		}	
}






	

