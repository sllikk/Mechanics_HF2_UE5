// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "WorldActors/Door.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PlayerComponent/Suit.h"
#include "PlayerComponent/HealthComponent.h"


DEFINE_LOG_CATEGORY(LogCharacter)
DEFINE_LOG_CATEGORY(LogCharacterResouce)


// Constructor character: initialization of all components and default settings of the character and its components for the game world
AMyCharacter::AMyCharacter()
{
	//default settings character movement, mesh and FirstPersonCamera
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	GetCapsuleComponent()->SetMassScale(NAME_Pawn, 60);
	GetCharacterMovement()->MaxAcceleration = m_MaxAcceleration;
	GetCharacterMovement()->Mass = m_MassCharacter;
	GetCharacterMovement()->JumpZVelocity = m_JumpHeight;
	GetCharacterMovement()->GravityScale = m_GravityScale;
	GetCharacterMovement()->AirControl = m_AirControl;
	GetCharacterMovement()->MaxFlySpeed = m_MaxSpeedFly;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(-20.f, 0.f, 80.f)); // Position the camera
	FirstPersonCamera->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCamera);
	Mesh1P->CastShadow = false;	
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
	// FleshLight Component for Character
	FlashLightComponent = CreateDefaultSubobject<UFlashLightComponent>(TEXT("FlashLightComponent"));
	FlashLightComponent->SetupAttachment(FirstPersonCamera);

	//PhysicsHandle forgrab and physics interact 
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle")); 
	PhysicsHandle->bSoftAngularConstraint = true;
	PhysicsHandle->bSoftLinearConstraint = true;
	PhysicsHandle->bInterpolateTarget = true;
	PhysicsHandle->LinearDamping = 200.0f;
	PhysicsHandle->LinearStiffness = 750.0f;
	PhysicsHandle->AngularDamping = 500.0f;
	PhysicsHandle->AngularStiffness = 1500.0f;
	PhysicsHandle->InterpolationSpeed = 50.0f;
	
	
}

// Destructor 
AMyCharacter::~AMyCharacter()
{

}


void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}


void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update Physics handle and grab object in World every frame
	if (PhysicsHandle->GrabbedComponent) 
	{
		FVector const& Start = FirstPersonCamera->GetComponentLocation();
		FVector const& NewLocation = Start + FirstPersonCamera->GetForwardVector() * m_DistanceTrace;	
		FRotator const& NewRotator = FirstPersonCamera->GetComponentRotation();
		PhysicsHandle->SetTargetLocationAndRotation(NewLocation, NewRotator);

	}

}


void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Assign functions to control the character and all actions associated with him in EIC
	if (UEnhancedInputComponent* EInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (UEnhancedInputComponent* EnhancedInput = dynamic_cast<UEnhancedInputComponent*>(EInputComponent))
		{						
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
			EnhancedInput->BindAction(RunAction, ETriggerEvent::Started, this, &AMyCharacter::Run);
			EnhancedInput->BindAction(RunAction, ETriggerEvent::Completed, this, &AMyCharacter::StopRun);
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::Jump);
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJumping);
			EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Started, this, &AMyCharacter::StartCrouch);
			EnhancedInput->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AMyCharacter::StopCrouch);
			EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacter::Interact);
			EnhancedInput->BindAction(FlashLightAction, ETriggerEvent::Started, this, &AMyCharacter::Flashlight);
			EnhancedInput->BindAction(GrabAction, ETriggerEvent::Started, this, &AMyCharacter::ToggleGrab);
			EnhancedInput->BindAction(TrowAction, ETriggerEvent::Started, this, &AMyCharacter::TrowObject);
		}		
	}	
	else
	{
		UE_LOG(LogCharacter, Error, TEXT("Failed to find an Enhanced Input Component!'"));	
	}

}


//--------------------------------------------------------------------------------------------------------------------------------------------------
//          Base Function character movement
//--------------------------------------------------------------------------------------------------------------------------------------------------


// Function Move for control character
void AMyCharacter::Move(const FInputActionValue& Value)
{
	const TSharedPtr<FVector2D> MovementVector = MakeShared<FVector2D>(Value.Get<FVector2D>());
		
	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector->Y);
		AddMovementInput(GetActorRightVector(), MovementVector->X);
		
	}
}

// Function Look for control character
void AMyCharacter::Look(const FInputActionValue& Value)
{
	const TSharedPtr<FVector2D> LookAxisVector = MakeShared<FVector2D>(Value.Get<FVector2D>());
		
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector->X);
		AddControllerPitchInput(LookAxisVector->Y);
	}

}

// Function Run for control character and play sound
void AMyCharacter::Run()
{
		GetCharacterMovement()->MaxWalkSpeed = m_MaxSpeedRun;
}

// Function StopRun for character to reduce running speed
void AMyCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = m_MaxSpeedWalk;
}

// Crouch 
void AMyCharacter::StartCrouch()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(43.0f); // we compress our collision to half its size
	GetCharacterMovement()->MaxWalkSpeedCrouched = m_MaxSpeedCrouch; // change speed
	//Default UE function 
	Crouch();

}

// Crouch 
void AMyCharacter::StopCrouch()
{
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f); //return scale collision how was it
	//Default UE function 
	UnCrouch();
}




// Interact Actors
void AMyCharacter::Interact()
{
	if (FirstPersonCamera == nullptr) return;
	{
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		FVector const& Start = FirstPersonCamera->GetComponentLocation();
		FVector const& End = Start + FirstPersonCamera->GetForwardVector() * m_LineTraceLength;
		
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
			{				
				DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f);
				DrawDebugPoint(GetWorld(), Start, 20, FColor::Green, false);
				DrawDebugPoint(GetWorld(), End, 20, FColor::Green, false);				

			//Door Actor for LineTrace 
			if (ADoor* DoorWood = Cast<ADoor>(HitResult.GetActor()))
			{
				DoorWood->Character = this;
				DoorWood->Interact();
			}
			}   
		}
	}


void AMyCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	

}

//--------------------------------------------------------------------------------------------------------------------------------------------------
//          Function action character
//--------------------------------------------------------------------------------------------------------------------------------------------------

void AMyCharacter::Flashlight()
{
	if (FlashLightComponent != nullptr)
	{
		FlashLightComponent->ToggleFlashLight();
	}
}

// Action Grab Object 
void AMyCharacter::ToggleGrab()
{
	if (PhysicsHandle->GrabbedComponent)
	{
		ReleaseComponent();
	}
	else
	{
		GrabComponent();
	}
}

// Physics grab
void AMyCharacter::GrabComponent()
{
	if (FirstPersonCamera == nullptr)return;
	{
		FHitResult GrabResults;
		FCollisionQueryParams QueryParams(FName(TEXT("RV_TRACE")), true, this);
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = false;
		QueryParams.bIgnoreTouches = true;
		FVector const& Start = FirstPersonCamera->GetComponentLocation();
		FVector const& End = Start + FirstPersonCamera->GetForwardVector() * m_DistanceTrace; 
	
		if (GetWorld()->LineTraceSingleByChannel(GrabResults, Start, End, ECC_GameTraceChannel2, QueryParams))
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
			DrawDebugPoint(GetWorld(), Start, 20, FColor::Red, false);
			DrawDebugPoint(GetWorld(), End, 20, FColor::Red, false);		
			
			UPrimitiveComponent* ComponentToGrab = GrabResults.GetComponent();

			if (!ComponentToGrab)return;
			if (!ComponentToGrab->IsSimulatingPhysics() || ComponentToGrab->GetMass() <= 0) 
			{
				DontInteract();
				return;
			}	

			const FBoxSphereBounds Bounds = ComponentToGrab->Bounds;	
			FVector const& CenterOfComponent = Bounds.Origin;
			FVector const& GrabLocation = CenterOfComponent;
			FRotator const& GrabRotation = ComponentToGrab->GetComponentRotation();
			if (ComponentToGrab->GetMass() <= m_MaxGrabMassObject && ComponentToGrab->IsSimulatingPhysics())
			{
				PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, GrabLocation, GrabRotation);
			}		

		}
	}
}

// Release Grab object
void AMyCharacter::ReleaseComponent()
{
	PhysicsHandle->ReleaseComponent();
}

// 
void AMyCharacter::DontInteract()
{

}


void AMyCharacter::TrowObject()
{
	if (PhysicsHandle->GrabbedComponent)
	{
		UPrimitiveComponent* TrowComponent = PhysicsHandle->GrabbedComponent;
		if(!TrowComponent) return;

		const FBoxSphereBounds Bounds = TrowComponent->Bounds;  
		FVector const& TrowCentreOfComponent = Bounds.Origin; 
		FVector const& TrowLocation = TrowCentreOfComponent;

		FVector const& TrowDirection = FirstPersonCamera->GetForwardVector();
		FVector const& GrabLocation = TrowLocation;
		FVector const& Force = TrowDirection * m_TrowImpulse;
		TrowComponent->AddVelocityChangeImpulseAtLocation(Force, GrabLocation);
		ReleaseComponent();

	}

}

	











