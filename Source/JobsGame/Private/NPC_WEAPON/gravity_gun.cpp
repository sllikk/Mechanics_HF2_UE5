// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_WEAPON/gravity_gun.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

class UEnhancedInputLocalPlayerSubsystem;

Ugravity_gun::Ugravity_gun()
{
	Gravity_Physics = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	const FSoftObjectPath FindSkeletalMesh(TEXT("/Game/Weapon/Gravity/GravityGun"));
	static TObjectPtr<USkeletalMesh> LoadMesh = nullptr;
	if (FindSkeletalMesh.IsValid())
	{
		LoadMesh = Cast<USkeletalMesh>(FindSkeletalMesh.TryLoad());
	}
	if (LoadMesh != nullptr)
	{
		USkeletalMeshComponent::SetSkeletalMesh(LoadMesh);
		USkeletalMeshComponent::SetCollisionProfileName("Weapons");
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("Error Load: %s"), *FindSkeletalMesh.ToString())
	}
	
}


void Ugravity_gun::BeginPlay()
{
	Super::BeginPlay();
}


void Ugravity_gun::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


void Ugravity_gun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void Ugravity_gun::AttachToWeapon(AMyCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	if (TargetCharacter == nullptr || Character->GetHasRifle())
	{
		return;
	}
	
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	// Set up action bindings
	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(WeaponMappingContext, 1);
		}
		if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Bind 
			EIC->BindAction(GrabAction, ETriggerEvent::Started, this, &Ugravity_gun::Gravity_Grab);	
			EIC->BindAction(TrowAction, ETriggerEvent::Started, this, &Ugravity_gun::Gravity_Trow);	
		}
		
	}
}


void Ugravity_gun::Gravity_Grab()
{
}


void Ugravity_gun::Gravity_Trow()
{

}


void Ugravity_gun::Gravity_Realese()
{
	UE_LOG(LogActor, Warning, TEXT("Release"));

}
