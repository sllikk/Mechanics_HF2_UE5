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
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/SceneComponent.h"

DEFINE_LOG_CATEGORY(LogCharacter)
DEFINE_LOG_CATEGORY(LogCharacterResouce)


AMyCharacter::AMyCharacter()
{
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
	
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle")); 
	PhysicsHandle->bSoftAngularConstraint = true;
	PhysicsHandle->bSoftLinearConstraint = true;
	PhysicsHandle->bInterpolateTarget = true;
	PhysicsHandle->LinearDamping = 200.0f;
	PhysicsHandle->LinearStiffness = 750.0f;
	PhysicsHandle->AngularDamping = 500.0f;
	PhysicsHandle->AngularStiffness = 1500.0f;
	PhysicsHandle->InterpolationSpeed = 50.0f;

	FlashLightComponent = CreateDefaultSubobject<UFlashLightComponent>(TEXT("FlashLightComponent"));
	FlashLightComponent->SetupAttachment(FirstPersonCamera);
	
}


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

	// Load Sound Resource for Character
	TArray<FResourceSound> ResourceToLoad = {
		{"/Game/Sound/ActorSound/Cue/Sprint_Cue", nullptr},
		{"/Game/Sound/ActorSound/Cue/No_Interact_Cue", nullptr},
		{"/Game/Sound/ActorSound/Cue/Interact_Cue", nullptr},	
	};		

	for (FResourceSound& Resource : ResourceToLoad)
	{
		Resource.LoadResource = LoadObject<UObject>(nullptr, *Resource.ResourcePath);
		if (Resource.LoadResource)
		{
			UE_LOG(LogCharacterResouce, Warning, TEXT("Loaded: %s"), *Resource.ResourcePath)
		}
		else
		{
			UE_LOG(LogCharacterResouce, Warning, TEXT("Error Loaded: %s"), *Resource.ResourcePath)
		}

	}	
	for (const FResourceSound& Resource : ResourceToLoad)
	{
		USoundBase* SoundLoad = Cast<USoundBase>(Resource.LoadResource);
		if (SoundLoad != nullptr)
		{
			SoundBase.Add(SoundLoad);
		}
	}
}


void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PhysicsHandle->GrabbedComponent) 
	{
		 FVector const& Start = FirstPersonCamera->GetComponentLocation();
		 FVector const& NewLocation = Start + FirstPersonCamera->GetForwardVector() * m_DistanceTrace;	
		 FRotator const& NewRotator = FirstPersonCamera->GetComponentRotation();
		PhysicsHandle->SetTargetLocationAndRotation(NewLocation, NewRotator);
		DebugObjectGrab();
		
	}
}


void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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
			EnhancedInput->BindAction( ToggleGrabAction, ETriggerEvent::Started, this, &AMyCharacter::ToggleGrabObject);
			EnhancedInput->BindAction(TrowAction, ETriggerEvent::Started, this, &AMyCharacter::TrowObject);
			EnhancedInput->BindAction(FleshLightAction, ETriggerEvent::Started, this, &AMyCharacter::Fleshlight);

		}		
	}	
	else
	{
		UE_LOG(LogCharacter, Error, TEXT("Failed to find an Enhanced Input Component!'"));	
	}

}


void AMyCharacter::Move(const FInputActionValue& Value)
{
	const TSharedPtr<FVector2D> MovementVector = MakeShared<FVector2D>(Value.Get<FVector2D>());
		
	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector->Y);
		AddMovementInput(GetActorRightVector(), MovementVector->X);
		
	}
}


void AMyCharacter::Look(const FInputActionValue& Value)
{
	const TSharedPtr<FVector2D> LookAxisVector = MakeShared<FVector2D>(Value.Get<FVector2D>());
		
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector->X);
		AddControllerPitchInput(LookAxisVector->Y);
	}

}


void AMyCharacter::Run()
{

	if (SoundBase[0] != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SoundBase[0], GetActorLocation());
		GetCharacterMovement()->MaxWalkSpeed = m_MaxSpeedRun;
	}
	 
}


void AMyCharacter::StopRun()
{

	GetCharacterMovement()->MaxWalkSpeed = m_MaxSpeedWalk;

}


void AMyCharacter::StartCrouch()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(43.0f);
	GetCharacterMovement()->MaxWalkSpeedCrouched = m_MaxSpeedCrouch;
	Crouch();

}


void AMyCharacter::StopCrouch()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	UnCrouch();
}


void AMyCharacter::AddIgnoredActorToLineTrace(const FName& GroupName, FCollisionQueryParams& QueryParams)
{
	TArray<AActor*> IgnoredActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), GroupName, IgnoredActors);
	
	for  (const AActor* ActorIgnored : IgnoredActors)
	{
		QueryParams.AddIgnoredActor(ActorIgnored);
	}
}


void AMyCharacter::Interact()
{
	
	if (FirstPersonCamera == nullptr) return;
	{
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.TraceTag = "InteractChannel";
		AddIgnoredActorToLineTrace("IgnoreGroup", QueryParams);
		AddIgnoredActorToLineTrace("IgnoreGroup2", QueryParams);

		FVector const& Start = FirstPersonCamera->GetComponentLocation();
		FVector const& End = Start + FirstPersonCamera->GetForwardVector() * m_LineTraceLength;
		
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
			{				
				DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f);
				DrawDebugPoint(GetWorld(), Start, 20, FColor::Green, false);
				DrawDebugPoint(GetWorld(), End, 20, FColor::Green, false);				
 
				ADoor* DoorWood = Cast<ADoor>(HitResult.GetActor());
						
					if (DoorWood)
					{
						DoorWood->Character = this;
						DoorWood->Interact();
					}
			}
		}
	}

void AMyCharacter::GrabComponents()
{
	if (FirstPersonCamera == nullptr) return;
	{
		FHitResult GrabResults;
		FCollisionQueryParams QueryParams(FName(TEXT("RV_TRACE")), true, this);
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = false;
		 FVector const& Start = FirstPersonCamera->GetComponentLocation();
		 FVector const& End = Start + FirstPersonCamera->GetForwardVector() * m_DistanceTrace; 
	
		if (GetWorld()->LineTraceSingleByChannel(GrabResults, Start, End, ECC_GameTraceChannel2, QueryParams))
		{
				DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
				DrawDebugPoint(GetWorld(), Start, 20, FColor::Red, false);
				DrawDebugPoint(GetWorld(), End, 20, FColor::Red, false);		
			
			UPrimitiveComponent* ComponentToGrab = GrabResults.GetComponent();

			if (!ComponentToGrab)return;
			
			const FBoxSphereBounds Bounds = ComponentToGrab->Bounds;	
			FVector const& CenterOfComponent = Bounds.Origin;
			FVector const& GrabLocation = CenterOfComponent;
			
			FRotator const& GrabRotation = ComponentToGrab->GetComponentRotation();
			FRotator AddGrabRotation(5,0, 0);
			FRotator const& NewGrabRotatator = GrabRotation + AddGrabRotation;

			if (ComponentToGrab->GetMass() <= m_MaxGrabMassObject && ComponentToGrab->IsSimulatingPhysics())
			{
				if (SoundBase[2] != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, SoundBase[2], GetActorLocation());
					PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, GrabLocation, NewGrabRotatator);
				}
			}
			else
			{
				DontInteract();
			}
			}
			else
			{
				DontInteract();		
			}		
		}
		
	}


void AMyCharacter::DebugObjectGrab()
{
	const FString& MassComponent = FString::Printf(TEXT("Mass: %2.f"), PhysicsHandle->GrabbedComponent->GetMass());

	const FString& LocationDebug = FString::Printf(TEXT("Loc: X = %2.f, Y = %2.f, Z = %2.f"), PhysicsHandle->GrabbedComponent->GetComponentLocation().X,
		PhysicsHandle->GrabbedComponent->GetComponentLocation().Y, PhysicsHandle->GrabbedComponent->GetComponentLocation().Z);

	FVector const& TextLocation = PhysicsHandle->GrabbedComponent->GetComponentLocation() + FVector(0,0,10);
	const FColor ColorDebug = FColor::White;

	DrawDebugString(GetWorld(), TextLocation,  MassComponent, nullptr, ColorDebug, 0, false);
	DrawDebugString(GetWorld(), TextLocation + FVector(0, 0, 1), LocationDebug, this, ColorDebug, false);

}



void AMyCharacter::ReleaseComponent()
{
	PhysicsHandle->ReleaseComponent();
}


void AMyCharacter::ToggleGrabObject()
{
	if (PhysicsHandle->GrabbedComponent)
	{
		ReleaseComponent();
	}
	else
	{
		GrabComponents();
	}
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
		FVector const& Force = TrowDirection * m_TrowImpulce;
		TrowComponent->AddVelocityChangeImpulseAtLocation(Force, GrabLocation);
		ReleaseComponent();

	}

	
}


void AMyCharacter::DontInteract()
{

	UE_LOG(LogCharacter, Warning, TEXT("No interact"));

	if (SoundBase[1] != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SoundBase[1], GetActorLocation());
	}
	
}



void AMyCharacter::Fleshlight()
{
	if (FlashLightComponent != nullptr)
	{
		FlashLightComponent->ToggleFlashLight();
	}
}












