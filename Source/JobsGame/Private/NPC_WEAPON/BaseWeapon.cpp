﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "JobsGame/JobsGame.h"
#include "Kismet/GameplayStatics.h"
#include "Property/ImpactEffectHandler.h"
#include "Property/object_pool.h"
#include "Shared/bullet_decal.h"
#include "Shared/Shell.h"

DEFINE_LOG_CATEGORY(LogWeapon);

// Sets default values
ABaseWeapon::ABaseWeapon() 
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	WeaponSkeletalMeshComponent->SetCollisionProfileName("Weapons");
	RootComponent = WeaponSkeletalMeshComponent;

	imaxAmmo = 30;
	m_flBulletSpread = 0.5;
	fSocketName = TEXT("Muzzle");
	icurrentAmmo = imaxAmmo;
	imaxInventoryAmmo = 100;
	m_flReloadTime = 2.0f;
	m_flmaxTraceLength = 10000.0f;
	m_flMaxPhysicsImpulse = 150.0f;
	idamage = 4;
	
	FireSound = nullptr;
	ReloadSound = nullptr;
	MuzzleFlash = nullptr;

	blsReload = false;
	blsPrimaryAttack = false;

	SwitchSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Sound/Weapon/Cue/switch_burst_Cue"));   // Shared sound 

	//hit_physics_material =  {"", "", "", ""};
	Tags.Add(FName("Interactive"));
	
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	GetWeaponMeshComponent()->SetSimulatePhysics(true);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void ABaseWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	Super::EndPlay(EndPlayReason);


	/*
	// Set up action bindings
	if (const APlayerController* PlayerController = Cast<const APlayerController>(Player->GetController()))                                                         // this dont work call error 
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(WeaponMappingContext);
		}
	}
*/

}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* this only func for player  */
void ABaseWeapon::AttachWeapon(AMyCharacter* Character, const FName& SocketName)
{
	Player = Character;

	if(Player == nullptr || Player->GetHasRifle())
	{
		return;
	}
	
	// Attach the weapon to the First Person Character
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Player->GetMesh1P(), AttachmentRules, SocketName);
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);
	
	// Set up action bindings
	if (const APlayerController* PlayerController = Cast<const APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(WeaponMappingContext, 1);
		}

		if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerController->InputComponent)) // Input Enhanced System 
		{
			EIC->BindAction(PrimaryAttackAction, ETriggerEvent::Started, this, &ABaseWeapon::StartAttack);
			EIC->BindAction(PrimaryAttackAction, ETriggerEvent::Completed, this, &ABaseWeapon::StopAttack);
			EIC->BindAction(SecondaryAttackAction, ETriggerEvent::Started, this, &ABaseWeapon::SecondaryAttack);
			EIC->BindAction(ReloadAction, ETriggerEvent::Started, this, &ABaseWeapon::Reload);
		}
	}
}


// Start and stop this fun for auto or single fire 
void ABaseWeapon::StartAttack()
{
	if (GetCurrentAmmo() <= 0 && SwitchSound != nullptr)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, SwitchSound, GetActorLocation());	
	}
	
	GetWorld()->GetTimerManager().SetTimer(PrimaryAttackTimer, this,  &ABaseWeapon::PrimaryAttack, GetAttackRate(), true);
	
	PrimaryAttack();

}

void ABaseWeapon::StopAttack()
{

	GetWorld()->GetTimerManager().ClearTimer(PrimaryAttackTimer);

}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /* this is the primary attack of our weapon and its general logic of settings such as spread,
		range, sounds, physical impact, and so on are universally found in the successor classes */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ABaseWeapon::PrimaryAttack()
{
	if (GetCurrentAmmo() <= 0 || blsReload)
	{
		Reload();
		return;
	}

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bReturnPhysicalMaterial = true;
	const FVector& Start = GetWeaponMeshComponent()->GetSocketLocation(GetSocketName());
	const FVector& ForwardVector = GetShotForwardVector();
	const FVector& Spread = CalculateBulletSpread(ForwardVector);
	const FVector& End =  Start + (Spread * GetMaxShootDistance());

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, COLLISION_TRACE_WEAPON, QueryParams);
	
	blsPrimaryAttack = true;
	EDamageType DamageType = EDamageType::DMG_BULLET;  
	
		ConsumeAmmo(1);
		SpawnEmitter();
		PhysicsTraceLogic(HitResult);

	#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT

	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 2);
	DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 10, FColor::Black, false, 2);	

	#endif

	if (AActor* Actor = HitResult.GetActor())
	{
		auto Effect = Cast<AImpactEffectHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AImpactEffectHandler::StaticClass()));
		Effect->EffectForSurface(HitResult);

		ApplyDamageHitActor(Actor, GetDamageAmounth(), DamageType);
	}
	
}

void ABaseWeapon::SecondaryAttack()
{
// only virtual
	
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void ABaseWeapon::Reload()
{
	if ( blsReload || GetCurrentAmmo() == GetMaxAmmo() || GetInvAmmo() == 0)
	{
		return;
	}
	blsReload = true;		

	if (ReloadSound != nullptr)                /* Reload Sound specific for weapon */
	{
		UGameplayStatics::SpawnSoundAtLocation(this, ReloadSound, GetActorLocation());
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer,  this, &ABaseWeapon::FinishReload, GetReloadTime(), false);   // Reload Timer

}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void ABaseWeapon::FinishReload()
{
	int32 AmmoToAdd = FMath::Min(GetInvAmmo(), imaxAmmo - GetCurrentAmmo());
	SetInvAmmo(GetInvAmmo() - AmmoToAdd);

	icurrentAmmo += AmmoToAdd;
	blsReload = false;

	GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);
	
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void ABaseWeapon::Interact(AActor* Actor) // Interface for grab weapon
{
	if (Actor && Actor->IsA(AMyCharacter::StaticClass()))
	{
		const TObjectPtr<AMyCharacter> PlayerCharacter = Cast<AMyCharacter>(Actor);
		if (PlayerCharacter != nullptr)
		{
			GetWeaponMeshComponent()->SetSimulatePhysics(false);
			GetWeaponMeshComponent()->SetCollisionProfileName("Weapons");
			PlayerCharacter->AddWeaponToInventory(this); // Add Character inventory
			AttachWeapon(PlayerCharacter, GetNameAttachSocket());
		}
	}
}


/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void ABaseWeapon::PhysicsTraceLogic(const FHitResult& HitResult)   // physics logic on shoot
{
	UPrimitiveComponent* PhysicsComponent = HitResult.GetComponent();
	
	if (PhysicsComponent != nullptr)
	{

		if (PhysicsComponent->IsSimulatingPhysics())
		{
			const FVector ImpulseDirection = (HitResult.ImpactPoint - HitResult.TraceStart).GetSafeNormal();
			PhysicsComponent->AddImpulse(ImpulseDirection * m_flMaxPhysicsImpulse, NAME_None, true);		
		}
		else
		{
			SpawnDecals(HitResult);
		}		
	}
}

void ABaseWeapon::ApplyDamageHitActor(AActor* Actor, int32 damage, EDamageType Damage)
{
	if (Actor != nullptr)
	{
		if (Idamageable* IdamageableActor = Cast<Idamageable>(Actor))
		{
			IdamageableActor->HandleDamage(damage, Damage);
		}
	}
	
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void ABaseWeapon::SpawnEmitter()   
{
	if (FireSound != nullptr)    // Sound Fire
	{
		UGameplayStatics::SpawnSoundAtLocation(this, FireSound, GetActorLocation());
	}
	
	// try and play a firing animation if specified
	if (aminPrimaryAttack != nullptr)
	{
		// Get the animation object for the arms mesh
		const TObjectPtr<UAnimInstance> AnimInstance = Player->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(aminPrimaryAttack, 0.9f);
		}
			
	}

	ShellDrop(); // shell dropping spawn
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void ABaseWeapon::ConsumeAmmo(int32 iAmmo)
{
	icurrentAmmo = FMath::Clamp(icurrentAmmo - iAmmo, 0.0f, imaxAmmo);
	
}


void ABaseWeapon::EmmiterAINoise()
{

	
}


void ABaseWeapon::SpawnDecals(const FHitResult& TraceResult)
{
/*
	if (pool_object_decal != nullptr)
	{
		TObjectPtr<Abullet_decal> spawndecal_bullet = pool_object_decal->GetObject<Abullet_decal>();

		if (spawndecal_bullet != nullptr)
		{
			spawndecal_bullet->SetActorLocation(TraceResult.Location);
			spawndecal_bullet->SetActorRotation(TraceResult.ImpactNormal.Rotation());
			ArrayActors.Emplace(spawndecal_bullet);
			GetWorld()->GetTimerManager().SetTimer(TimePoolObject_Decals, this, &ABaseWeapon::PoolRelease_Decals, 5.0f, true);
		}
	}
	*/	
}

void ABaseWeapon::PoolRelease_Decals()
{
	/*
		if (ArrayActors.Num() > 0)
		{
			for (int32 i = 0; i < ArrayActors.Num(); i++)
			{
				pool_object_decal->ReleaseObject(ArrayActors[i]);
			}	
			 ArrayActors.Empty();
		}
	
		*/
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	/* this is a virtual function that spawns cartridges, sets a timer for their return to the pool,
	    the implementation itself is located in classes that are descendants of this class */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void ABaseWeapon::ShellDrop() 
{
	GetWorld()->GetTimerManager().SetTimer(TimePoolObject, this, &ABaseWeapon::ObjectPoolRelease, 1.2, true);
}


void ABaseWeapon::ObjectPoolRelease()
{
	GetWorld()->GetTimerManager().ClearTimer(TimePoolObject);

}


