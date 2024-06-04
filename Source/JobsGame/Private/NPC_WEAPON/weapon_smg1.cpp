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

	Object_Pool = CreateDefaultSubobject<Aobject_pool>(TEXT("ObjectPool"));
	
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

	if (PoolClass != nullptr)
	{
		Object_Pool = GetWorld()->SpawnActor<Aobject_pool>(PoolClass);
		if (Object_Pool != nullptr )
		{
			Object_Pool->InitializePool(AShell::StaticClass(), 70);
			UE_LOG(LogTemp, Log, TEXT("ObjectPool initialized with class: %s"), *AShell::StaticClass()->GetName());	
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ObjectPool is not initialized."));
	}
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

void Aweapon_smg1::SpawnShell()
{
	if (Object_Pool)
	{
		AShell* ShellSpawn = Cast<AShell>(Object_Pool->GetObject());

		if (ShellSpawn != nullptr)
		{
			const FVector LocationSpawn = SpawnShellArrow->GetComponentLocation();
			FVector ForwardVector = SpawnShellArrow->GetForwardVector();

			ShellSpawn->SetActorLocation(LocationSpawn);
			ShellSpawn->SetActorRotation(FRotator::ZeroRotator);
			ShellSpawn->SetActorHiddenInGame(false);
			ShellSpawn->GetMeshBullet()->AddImpulse(ForwardVector * 500, NAME_None, true);
			Array.Add(ShellSpawn);

			GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &Aweapon_smg1::ReturnShellToPool, 1.5, false);
		}
	}	
}

void Aweapon_smg1::ReturnShellToPool()
{
	if(Array.Num() > 0)
	{
		for (int16 i = 0; i < Array.Num(); ++i)
		{
			Object_Pool->ReleaseObject(Array[i]);
		}
		
	}


}


	

