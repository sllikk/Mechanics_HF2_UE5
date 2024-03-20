// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MyCharacter.h"
#include "WorldActors/WoodDoor.h" 
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogCharacter)


AMyCharacter::AMyCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
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


}


AMyCharacter::~AMyCharacter()
{

}


void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
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

		}		
	}	
	
	else
	{
		UE_LOG(LogCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component!'"));	
	}

}


void AMyCharacter::Move(const FInputActionValue& Value)
{
	TSharedPtr<FVector2D> MovementVector = MakeShared<FVector2D>(Value.Get<FVector2D>());
		
	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector->Y);
		AddMovementInput(GetActorRightVector(), MovementVector->X);
		
	}
}


void AMyCharacter::Look(const FInputActionValue& Value)
{
	TSharedPtr<FVector2D> LookAxisVector = MakeShared<FVector2D>(Value.Get<FVector2D>());
		
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector->X);
		AddControllerPitchInput(LookAxisVector->Y);
	}

}


void AMyCharacter::Run()
{
	if (SprintSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SprintSound, GetActorLocation());
	}
	
	GetCharacterMovement()->MaxWalkSpeed = m_MaxSpeedRun;

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


void AMyCharacter::Interact()
{
	
	if (FirstPersonCamera == nullptr) return;
	{
		
		FVector Start = FirstPersonCamera->GetComponentLocation();
		FVector End = Start + FirstPersonCamera->GetForwardVector() * m_LineTraceLength;
		
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2));
		
		for (auto& ObjectType : ObjectTypes)
		{
			FHitResult HitResult;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);

			if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, FCollisionObjectQueryParams(ObjectType), QueryParams))
			{				
				if (HitResult.bBlockingHit)
				{
					AWoodDoor* DoorWood = Cast<AWoodDoor>(HitResult.GetActor());
						
					if (DoorWood)
					{
						DoorWood->Character = this;
						DoorWood->Interact();
					}
				
				}
			}

		}
		
	}
		
}











