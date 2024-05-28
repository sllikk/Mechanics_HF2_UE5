﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"

#include "AIController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
	icurrentAmmo = imaxAmmo;
	imaxInventoryAmmo = 100;
	m_flReloadTime = 2.0f;
	blsReload = false;
}


// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Debug();

}

void ABaseWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	Super::EndPlay(EndPlayReason);
/*
	// Set up action bindings
	if (const APlayerController* PlayerController = Cast<const APlayerController>(Player->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(WeaponMappingContext);
		}
	}
*/
}


FVector ABaseWeapon::GetShotForwardVector() const
{
	// Get Controller Player
	TObjectPtr<AController> Controller = Player->GetController();

	if (Controller != nullptr)
	{
		// check this player controller
		if (Controller->IsA(APlayerController::StaticClass()))
		{
			TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(Controller);
			if (PlayerController != nullptr && PlayerController->PlayerCameraManager != nullptr)
			{
				// Get Direction Camera Player 
				return  PlayerController->PlayerCameraManager->GetActorForwardVector();
			}
		}
		// check, valid this npc controller 
		else if (Controller->IsA(AAIController::StaticClass()))
		{
			// Get direction npc
			return  Player->GetActorForwardVector();
		}
	}

	// return zero vector if error
	return FVector::ZeroVector;

}


void ABaseWeapon::LoadSkeletalMesh(const FString& Path) const
{
	const FSoftObjectPath FindSkeletalMesh(*Path);
	static TObjectPtr<USkeletalMesh> LoadMesh = nullptr;

	if (FindSkeletalMesh.IsValid())
	{
		LoadMesh = Cast<USkeletalMesh>(FindSkeletalMesh.TryLoad());
	}
	if (LoadMesh != nullptr)
	{
		WeaponSkeletalMeshComponent->SetSkeletalMesh(LoadMesh);
	}
	else
	{
		UE_LOG(LogWeapon, Warning, TEXT("Error Load: %s"), *FindSkeletalMesh.ToString())
	}
}


FVector ABaseWeapon::CalculateBulletSpread(const FVector& ShotDirection) const
{
	float HalfConeAngleRand = FMath::DegreesToRadians(m_flBulletSpread / 2.0f);
	FVector SpreadDirection = FMath::VRandCone(ShotDirection, HalfConeAngleRand);
	
	return SpreadDirection;
}


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
	Debug();
	
	// Set up action bindings
	if (const APlayerController* PlayerController = Cast<const APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(WeaponMappingContext, 1);
		}

		if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EIC->BindAction(FireAction, ETriggerEvent::Started, this, &ABaseWeapon::Fire);
			EIC->BindAction(ReloadAction, ETriggerEvent::Started, this, &ABaseWeapon::Reload);
		
		}
	}
}



void ABaseWeapon::Fire()
{
	if (Player == nullptr) return;

	if (GetCurrentAmmo() <= 0 && blsReload)
	{
		UE_LOG(LogWeapon, Warning, TEXT("No Ammo!!!!!!!!!"));	
		return;
	}

	UE_LOG(LogWeapon, Warning, TEXT("Fire"));	

	FHitResult HitResult;
	const FVector& Start = GetSkeletalMeshComponent()->GetSocketLocation(GetSocketName());
	const FVector& ForwardVector = GetShotForwardVector();
	const FVector& Sphread = CalculateBulletSpread(ForwardVector);
	const FVector& End =  Start + (Sphread * GetMaxShootDistance());

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
	{
		ConsumeAmmo(1);
		
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 2);
			DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 10, FColor::Black, false, 2);

			if (UPrimitiveComponent* Component = HitResult.GetComponent())
			{
				if (Component)
				{
					UE_LOG(LogWeapon, Warning, TEXT("BAMMM"));
				}
			}
	}
	
}



void ABaseWeapon::Reload()
{
	if (blsReload)
	{
		return;
	}
	if (GetCurrentAmmo() == GetMaxAmmo() || GetInvAmmo() == 0)
	{
		UE_LOG(LogWeapon, Warning, TEXT("Cannot reload: ammo is full or no ammo in inventory"));
		return;
	}
	blsReload = true;		
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer,  this, &ABaseWeapon::FinishReload, GetReloadTime(), false);   
}


void ABaseWeapon::FinishReload()
{
	int32 AmmoToAdd = FMath::Min(GetInvAmmo(), imaxAmmo - GetCurrentAmmo());
	SetInvAmmo(GetInvAmmo() - AmmoToAdd);
	icurrentAmmo += AmmoToAdd;
	blsReload = false;
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);
	
}


void ABaseWeapon::Debug() const					// only editor
{
	if (GEngine != nullptr)
	{
		const FString& Ammo = FString::Printf(TEXT("Ammo: %d, MaxAmmo: %d"), GetCurrentAmmo(), GetInvAmmo());
		 GEngine->AddOnScreenDebugMessage(3, -1, FColor::Yellow, Ammo);

	}

}


void ABaseWeapon::ConsumeAmmo(int32 iAmmo)
{
	icurrentAmmo = FMath::Clamp(icurrentAmmo - iAmmo, 0.0f, imaxAmmo);	\
}


