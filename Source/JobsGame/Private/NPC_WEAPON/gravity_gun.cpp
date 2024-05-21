﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_WEAPON/gravity_gun.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

class UEnhancedInputLocalPlayerSubsystem;

Ugravity_gun::Ugravity_gun()
{
	// DefaultProperty
	Gravity_Physics = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	Gravity_Physics->bSoftAngularConstraint = true;
	Gravity_Physics->bSoftLinearConstraint = true;
	Gravity_Physics->bInterpolateTarget = true;
	Gravity_Physics->LinearDamping = 50.0f;
	Gravity_Physics->LinearStiffness = 750.0f;
	Gravity_Physics->AngularDamping = 500.0f;
	Gravity_Physics->AngularStiffness = 1500.0f;
	Gravity_Physics->InterpolationSpeed = 50.0f;	

	m_flphyscanon_maxmass = 250.0f;
	m_flphyscanon_tracelength = 500.0f;
	m_flphyscannon_pullforce = 2000.0f;
	m_flphyscannon_minforce = 700.0f;
	m_flphyscannon_maxforce = 1500.0f;
	m_trace_sphere_radius = 15.0f;
	m_trace_sphere_halfheight = 30.0f;
	
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

	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(WeaponMappingContext);
		}
	}

}


void Ugravity_gun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PhysicsTick();
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
	if (const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
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
	if (Character->GetFirstPersonCamera() == nullptr) return;
	{
		TArray<FHitResult> HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredComponent(this);	
		
		FCollisionShape CollisionShape;
		CollisionShape.MakeSphere(GetTraceSphereRadius());
		
		const FVector& Start = GetSocketLocation("Muzzle");
		const FVector& End = Start + (Character->GetFirstPersonCamera()->GetForwardVector() * m_flphyscanon_tracelength);

		if ( GetWorld()->SweepMultiByChannel(HitResult, Start, End,  FQuat::Identity,ECC_Visibility, CollisionShape, QueryParams) )
		{
			for (const FHitResult ComponentHit : HitResult)
			{
				TObjectPtr<UPrimitiveComponent> Component = ComponentHit.GetComponent(); 
				if (Component != nullptr)
				{
					DrawDebugSphere(GetWorld(), ComponentHit.Location, GetTraceSphereRadius(), 32, FColor::Cyan, false, 2);
					DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 2);
					const FVector& GrabLocation = Component->GetComponentLocation();  
					const FRotator& Rotator = Component->GetComponentRotation(); 
					Gravity_Physics->GrabComponentAtLocationWithRotation(Component, NAME_None, GrabLocation, Rotator);
				}
			}	
		}
	}
	
}


void Ugravity_gun::Gravity_Trow()
{

}


void Ugravity_gun::Gravity_Realese()
{
	if (Gravity_Physics)
	{
		Gravity_Physics->ReleaseComponent();
	}
	
}

void Ugravity_gun::PhysicsTick() const
{
	if (Gravity_Physics->GrabbedComponent)
	{
		TObjectPtr<UPrimitiveComponent> Component = Gravity_Physics->GrabbedComponent;

		FVector const& Start = Character->GetFirstPersonCamera()->GetComponentLocation();
		FVector const& NewLocation = Start + Character->GetFirstPersonCamera()->GetForwardVector() * 150;	
		FRotator const& NewRotator = Character->GetFirstPersonCamera()->GetComponentRotation();

		Gravity_Physics->SetTargetLocationAndRotation(NewLocation, NewRotator);

	}
}
