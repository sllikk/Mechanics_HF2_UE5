// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_WEAPON/gravity_gun.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "Camera/CameraComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
class UEnhancedInputLocalPlayerSubsystem;

// Constructor to initialize default properties and load mesh
Ugravity_gun::Ugravity_gun()
{
	// Initialize default properties for physics handle
	Gravity_Physics = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	

	m_flphyscanon_maxmass = 250.0f;
	m_flphyscanon_tracelength = 5000.0f;
	m_flphyscannon_pullforce = 2000.0f;
	m_flphyscannon_minforce = 90.0f;
	m_flphyscannon_maxforce = 1500.0f;
	m_trace_sphere_radius = 20.0f;
	m_trace_sphere_halfheight = 30.0f;
	bIsPullingObject = false;
	
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

// Called when the game starts, adds component tags
void Ugravity_gun::BeginPlay()
{
	Super::BeginPlay();

	ComponentTag.Add("PhysCannon");
	ComponentTag.Add("Destruction");
	ComponentTag.Add("PhysicsObject");

	Gravity_Physics->bSoftAngularConstraint = true;
	Gravity_Physics->bSoftLinearConstraint = true;
	Gravity_Physics->bInterpolateTarget = true;
	Gravity_Physics->LinearDamping = 50.0f;
	Gravity_Physics->LinearStiffness = 750.0f;
	Gravity_Physics->AngularDamping = 500.0f;
	Gravity_Physics->AngularStiffness = 1500.0f;
	Gravity_Physics->InterpolationSpeed = 50.0f;	
	
}

// Called when the game ends, removes mapping context
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

// Called every frame, handles physics tick and object pulling
void Ugravity_gun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PhysicsTick();

	if (bIsPullingObject && CurrentPulledComponent && Gravity_Physics)
	{
		const FVector Start = Character->GetFirstPersonCamera()->GetComponentLocation();
		const FVector TargetLocation = CurrentPulledComponent->GetComponentLocation();
		float Distance = FVector::Dist(Start, TargetLocation);

		if (Distance > 300)
		{
			// Притягивание объекта к игроку
			FVector Direction = (Start - TargetLocation).GetSafeNormal();
			CurrentPulledComponent->AddForce(Direction * CurrentPulledComponent->GetMass() * m_flphyscannon_pullforce);
		}
		else
		{
			// Захват объекта
			const FRotator Rotator = CurrentPulledComponent->GetComponentRotation();
			Gravity_Physics->GrabComponentAtLocationWithRotation(CurrentPulledComponent, NAME_None, TargetLocation, Rotator);
			CurrentPulledComponent = nullptr; 
		}
	}

}


// Attaches the weapon to the character and sets up action bindings
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
	if (const APlayerController* PlayerController = Cast<const APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(WeaponMappingContext, 1);
		}
		if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Bind 
			EIC->BindAction(GrabAction, ETriggerEvent::Triggered, this, &Ugravity_gun::Gravity_Grab);	
			EIC->BindAction(GrabAction, ETriggerEvent::Completed, this, &Ugravity_gun::Gravity_Realese);	
			EIC->BindAction(TrowAction, ETriggerEvent::Started, this, &Ugravity_gun::Gravity_Trow);	
			EIC->BindAction(TrowAction, ETriggerEvent::Started, this, &Ugravity_gun::TrowImpulce);	
		}
		
	}
}


// Initiates object pulling when the grab action is triggered
void Ugravity_gun::Gravity_Grab()
{
	if (!Character || !Character->GetFirstPersonCamera()) return;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredComponent(this);	
	FCollisionShape CollisionShape;
	CollisionShape.MakeSphere(GetTraceSphereRadius());

	const FVector& Start = Character->GetFirstPersonCamera()->GetComponentLocation();
	const FVector& End = Start + (Character->GetFirstPersonCamera()->GetForwardVector() * 5000);

	if (GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Visibility, CollisionShape, QueryParams))
	{
		for (const FHitResult& ComponentHit : HitResults)
		{
			TObjectPtr<UPrimitiveComponent> Component = ComponentHit.GetComponent(); 
			if (!Component || !Component->IsSimulatingPhysics() || Component->GetMass() > GetPhyscanon_Maxmass()) continue;

			const TArray<FName>& Tags = Component->ComponentTags;	
			for (const FName& Tag : Tags)
			{
				if (ComponentTag.Contains(Tag))
				{
					#if WITH_EDITOR  
					DrawDebugSphere(GetWorld(), ComponentHit.Location, GetTraceSphereRadius(), 32, FColor::Cyan, false, 2);
					DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 2);
					#endif					

					bIsPullingObject = true;
					CurrentPulledComponent = Component;
					return;
				}
			}
		}
	}
}


// Throws the grabbed object with a specified force when the throw action is triggered
void Ugravity_gun::Gravity_Trow()
{
	if (Gravity_Physics->GrabbedComponent)
	{
		TObjectPtr<UPrimitiveComponent> TrowComponent = Gravity_Physics->GrabbedComponent;
		if(!TrowComponent) return;

		const FBoxSphereBounds SphereBounds = TrowComponent->Bounds;  
		FVector const& TrowCentreOfComponent = SphereBounds.Origin; 
		FVector const& TrowLocation = TrowCentreOfComponent;

		FVector const& TrowDirection = Character->GetFirstPersonCamera()->GetForwardVector();
		FVector const& GrabLocation = TrowLocation;
		FVector const& Force = TrowDirection * m_flphyscannon_maxforce;
		TrowComponent->AddVelocityChangeImpulseAtLocation(Force, GrabLocation);

		Gravity_Realese();
	}
}


// Releases the grabbed object and stops pullin
void Ugravity_gun::Gravity_Realese()
{
	if (Gravity_Physics)
	{
		bIsPullingObject = false;
		Gravity_Physics->ReleaseComponent();
	}
	
}

// Updates the position and rotation of the grabbed component based on camera direction
void Ugravity_gun::PhysicsTick() const
{
	if (Gravity_Physics->GrabbedComponent)
	{
		const TObjectPtr<UPrimitiveComponent> Component = Gravity_Physics->GrabbedComponent;

		FVector const& Start = GetSocketLocation("Muzzle");
		FVector const& TargetLocation = Start + Character->GetFirstPersonCamera()->GetForwardVector() * 200;    
		FRotator const& NewRotator = Character->GetFirstPersonCamera()->GetComponentRotation();
		
		Gravity_Physics->SetTargetLocationAndRotation(TargetLocation, NewRotator);
	}
}


// Performs impulse throw when the impulse action is triggered	
void Ugravity_gun::TrowImpulce() 
{
	if (Gravity_Physics->GrabbedComponent)
	{
		return;
	}
	
	if (Character == nullptr) return;
	{
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredComponent(this);	

		const FVector& Start = Character->GetFirstPersonCamera()->GetComponentLocation();
		const FVector& End = Start + (Character->GetFirstPersonCamera()->GetForwardVector() * 1000);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility ,QueryParams))
		{
			UPrimitiveComponent* Component = HitResult.GetComponent();
			if(!Component) return;	
			
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2);
			if (Component->IsSimulatingPhysics())
			{
				FBoxSphereBounds Bound = Component->Bounds;
				FVector Centre = Bound.Origin;
				FVector Location = Centre;
				FVector const& Force = HitResult.TraceEnd * m_flphyscannon_minforce;
				Component->AddImpulseAtLocation(Force, Location);	
				/*
				// Apply damage to the owning actor
				float DamageAmount = 50.0f;  // Example damage amount
				FDamageEvent DamageEvent;
				OwnerActor->TakeDamage(DamageAmount, DamageEvent, Character->GetController(), nullptr);
*/
			}
			
		}

	}

}
	


  