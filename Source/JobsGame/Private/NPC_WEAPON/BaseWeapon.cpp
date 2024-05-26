// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"
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
}

void ABaseWeapon::LoadSkeletalMesh(const FString& Path)
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
/*
void ABaseWeapon::LoadShellMesh(const FString& Path)
{
	const FSoftObjectPath FindShellMesh(*Path);
	static TObjectPtr<UStaticMesh> LoadMesh = nullptr;

	if (FindShellMesh.IsValid())
	{
		LoadMesh = Cast<UStaticMesh>(FindShellMesh.TryLoad());
	}
	if (LoadMesh != nullptr)
	{
		WeaponSkeletalMeshComponent->SetSkeletalMesh(LoadMesh);
	}
	else
	{
		UE_LOG(LogWeapon, Warning, TEXT("Error Load: %s"), *FindShellMesh.ToString())
	}
}
*/

void ABaseWeapon::AttachWeapon(AMyCharacter* Character)
{
	Player = Character;

	if(Player==nullptr || Player->GetHasRifle())
	{
		return;
	}
	
	// Attach the weapon to the First Person Character
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Player->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

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
		}
	
	}
}

void ABaseWeapon::Fire()
{
	UE_LOG(LogWeapon, Warning, TEXT("Fire"));	
}

