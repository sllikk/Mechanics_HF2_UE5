// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "JobsGame/JobsGame.h"
#include "Kismet/GameplayStatics.h"
#include "NPC_WEAPON/BaseWeapon.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Player/BasePlayerCameraManager.h"
#include "Shared/interact.h"
#include "Shared/Resourse.h"

DEFINE_LOG_CATEGORY(LogCharacter)
DEFINE_LOG_CATEGORY(LogCharacterResouce)

// Constructor character: initialization of all components and default settings of the character and its components for the game world
AMyCharacter::AMyCharacter()
      : m_HasRifle(false),m_MaxSpeedWalk(500.0f),m_MaxSpeedRun(700.0f), m_MaxSpeedCrouch(400.0f),
		m_MaxAcceleration(2048.0f),m_GravityScale(1.0f),m_AirControl(0.8f),m_MaxSpeedFly(200.0f),m_MassCharacter(20.0f),m_JumpHeight(300.0f),
	    m_DistanceTrace(190.0f),m_MaxGrabMassObject(80.0f), m_TrowImpulse(250.0f), m_blsDead(false), bls_discharger_suit(false), m_imaxhealth(100), m_maxcharger_suit(100)
{
	//default settings character movement, mesh and FirstPersonCamera
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	GetCharacterMovement()->MaxAcceleration = m_MaxAcceleration;
	GetCharacterMovement()->JumpZVelocity = m_JumpHeight;
	GetCharacterMovement()->GravityScale = m_GravityScale;
	GetCharacterMovement()->AirControl = m_AirControl;
	GetCharacterMovement()->MaxFlySpeed = m_MaxSpeedFly;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(-20.f, 0.f, 80.f)); // Position the camera
	FirstPersonCamera->bUsePawnControlRotation = true;

	// FleshLight Component for Character
	FlashLightComponent = CreateDefaultSubobject<UFlashLightComponent>(TEXT("FlashLightComponent"));
	FlashLightComponent->SetupAttachment(FirstPersonCamera);
	
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(false);
	Mesh1P->SetupAttachment(FirstPersonCamera);
	Mesh1P->CastShadow = false;	
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
	
	//PhysicsHandle for grab and physics interact 
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle")); 

	// WeaponIndex
	m_icurrent_weapon_index = -1;
	m_icurrent_health = m_imaxhealth;
	m_icharger_suit = m_maxcharger_suit;
	strPlayerName = "Player";
	flinteract_sphere_radius = 25.0f;

	array_grab_name.Add(FName("PhysicsObject"));
	array_grab_name.Add(FName("Destruction")); 

	array_interact_name.Add(FName("Interactive"));
	array_interact_name.Add(FName("Trigger"));
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCharacterMovement()->Mass = m_MassCharacter;
	GetCapsuleComponent()->SetMassScale(NAME_Pawn, 60);
	
	PhysicsHandle->bSoftAngularConstraint = true;
	PhysicsHandle->bSoftLinearConstraint = true;
	PhysicsHandle->bInterpolateTarget = true;
	PhysicsHandle->LinearDamping = 50.0f;
	PhysicsHandle->LinearStiffness = 750.0f;
	PhysicsHandle->AngularDamping = 500.0f;
	PhysicsHandle->AngularStiffness = 1500.0f;
	PhysicsHandle->InterpolationSpeed = 50.0f;

	SoundResourceLoad();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------------------------------------------------------------------

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickPhysicsHandle();

	if (GEngine != nullptr)
	{
		const FString& strHealth = FString::Printf(TEXT("Health: %d"), m_icurrent_health);
		const FString& strSuit = FString::Printf(TEXT("Suit: %d"), m_icharger_suit);

		GEngine->AddOnScreenDebugMessage(1, 120, FColor::Yellow ,strHealth);	  
		GEngine->AddOnScreenDebugMessage(2, 120, FColor::Yellow ,strSuit);	  
		
	}

}
//--------------------------------------------------------------------------------------------------------------------------------------------------

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
			EnhancedInput->BindAction(Switch1Action, ETriggerEvent::Started, this, &AMyCharacter::SwitchWeapon1);
			EnhancedInput->BindAction(Switch2Action, ETriggerEvent::Started, this, &AMyCharacter::SwitchWeapon2);
			EnhancedInput->BindAction(Switch3Action, ETriggerEvent::Started, this, &AMyCharacter::SwitchWeapon3);
		}		
	}	
	else
	{
		UE_LOG(LogCharacter, Error, TEXT("Failed to find an Enhanced Input Component!'"));	
	}

}
//--------------------------------------------------------------------------------------------------------------------------------------------------

void AMyCharacter::SoundResourceLoad() 
{
	TArray<FResourceLoad> ResourceToLoad = {
		FResourceLoad(TEXT("/Game/Sound/ActorSound/Cue/Sprint_Cue"), nullptr),
		FResourceLoad(TEXT("/Game/Sound/ActorSound/Cue/Interact_Cue"), nullptr),
		FResourceLoad(TEXT("/Game/Sound/ActorSound/Cue/No_Interact_Cue"), nullptr),
		};
	for (FResourceLoad& Resource : ResourceToLoad)
	{
		Resource.LoadedResource = LoadObject<UObject>(nullptr, *Resource.ResourcePath);
		if (!Resource.LoadedResource)
		{
			UE_LOG(LogCharacter, Warning, TEXT("Error load: %s"), *Resource.ResourcePath)
		}
	}
	for (const FResourceLoad& Resource : ResourceToLoad)
	{
		USoundBase* SoundBase = Cast<USoundBase>(Resource.LoadedResource);
		if (SoundBase != nullptr)
		{
			CharacterSound.Add(SoundBase);
		}
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
//--------------------------------------------------------------------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------------------------------------------------------------------

// Function Run for control character and play sound
void AMyCharacter::Run()
{
	if (CharacterSound.IsValidIndex(0) && CharacterSound[0] != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CharacterSound[0], GetActorLocation());	
		GetCharacterMovement()->MaxWalkSpeed = m_MaxSpeedRun;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

// Function StopRun for character to reduce running speed
void AMyCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = m_MaxSpeedWalk;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

// Crouch 
void AMyCharacter::StartCrouch()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(43.0f); // we compress our collision to half its size
	GetCharacterMovement()->MaxWalkSpeedCrouched = m_MaxSpeedCrouch; 
	Crouch();

}
//--------------------------------------------------------------------------------------------------------------------------------------------------

// Crouch 
void AMyCharacter::StopCrouch()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f); //return scale collision how was it
	UnCrouch();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

// Interact Actors
void AMyCharacter::Interact()
{
	if (FirstPersonCamera == nullptr) return;
	{
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		FVector const&  StartLocation = FirstPersonCamera->GetComponentLocation();
		FVector const&  EndLocation = StartLocation + (FirstPersonCamera->GetForwardVector() * m_DistanceTrace);
		
		if (GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, COLLISION_INTERACT_TRACE,
			FCollisionShape::MakeSphere(flinteract_sphere_radius), QueryParams))
		{
			TObjectPtr<AActor> HitActor = HitResult.GetActor();
			if (HitActor != nullptr)
			{	
				const TArray<FName>& TagsActor = HitActor->Tags;
				for (const FName& InteractTags : TagsActor)
				{
					if (array_interact_name.Contains(InteractTags))
					{
						if (HitActor->GetClass()->ImplementsInterface(Uinteract::StaticClass()))
						{
							#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
							DrawDebugSphere(GetWorld(), HitResult.Location, 20, 20, FColor::Green);
							#endif
							
							if (Iinteract* InteractableActor = Cast<Iinteract>(HitActor))
							{
								InteractableActor->Interact(this);
							}
						}
					}
				}	
					
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

void AMyCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	

}
//--------------------------------------------------------------------------------------------------------------------------------------------------

void AMyCharacter::TickPhysicsHandle() const
{
	// Update Physics handle and grab object in World every frame
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent) 
	{
		FVector const& Start = FirstPersonCamera->GetComponentLocation();
		FVector const& NewLocation = Start + FirstPersonCamera->GetForwardVector() * m_DistanceTrace;	
		FRotator const& NewRotator = FirstPersonCamera->GetComponentRotation();
		PhysicsHandle->SetTargetLocationAndRotation(NewLocation, NewRotator);

		// Release Component if distance > 250
		if (FVector::Dist(Start, PhysicsHandle->GrabbedComponent->GetComponentLocation() ) > 250)
		{
			PhysicsHandle->ReleaseComponent();
		}
	}
}

bool AMyCharacter::RestoreHealth(int32 HealthAmounth)
{
	m_icurrent_health += HealthAmounth;
	m_icurrent_health = FMath::Min(m_icurrent_health, m_imaxhealth);
	
	return m_icurrent_health < m_imaxhealth;
}

bool AMyCharacter::RestoreSuit(int32 SuitAmounth)
{
	m_icharger_suit += SuitAmounth;
	m_icharger_suit = FMath::Min(m_icharger_suit, m_maxcharger_suit);
	
	return m_icharger_suit < m_maxcharger_suit;
}

/*----------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------*/
void AMyCharacter::HandleDamage(int32 damage_amounth, EDamageType DamageType)
{
	if(ISDead() || GetPlayerHealth() <= 0) return;	

	// Check if the character has armor and whether the armor protects against this type of damage
	if (m_icharger_suit > 0 && !(DamageType & (EDamageType::DMG_FALL | EDamageType::DMG_DROWN | EDamageType::DMG_POISON | EDamageType::DMG_RADIATION)))
	{
		constexpr float ArmorRatio = 0.3f;  // Percentage of damage that armor absorbs (30%)
		constexpr float ArmorBonus = 1.0f;  // Armor coefficient

	// Calculate how much damage will be dealt to health (NewDamage) and how much armor will absorb (ArmorDamage)
	float NewDamage = damage_amounth * ArmorRatio; // health damage calc
	float ArmorDamage = (damage_amounth - NewDamage) * ArmorBonus;

	if (ArmorDamage < 1.0f)
	{
		ArmorDamage = 1.0f;
	}
		// If the armor is not enough to absorb all the damage
		if (ArmorDamage > m_icharger_suit)
		 {
			ArmorDamage = m_icharger_suit;
			NewDamage = damage_amounth - (ArmorDamage * (1.0f / ArmorBonus));
			m_icharger_suit = 0;  
		}
		else
		{
			m_icharger_suit -= ArmorDamage;
		}

		m_idamageSave =  damage_amounth = static_cast<int32>(NewDamage);

	}

	m_icurrent_health = FMath::Clamp(m_icurrent_health - damage_amounth, 0.0f, m_imaxhealth);


	if (GetPlayerHealth() <= 0)
	{
		Dead();
	}
	
}

void AMyCharacter::Dead()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (ABasePlayerCameraManager* CameraManager = Cast<ABasePlayerCameraManager>(PlayerController->PlayerCameraManager))
		{
			CameraManager->PlayDeathCameraAnim();
		}
	}
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
//--------------------------------------------------------------------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------------------------------------------------------------------

// Physics grab
void AMyCharacter::GrabComponent()
{
	if (FirstPersonCamera == nullptr) return;
	{
		FHitResult GrabResults;
		FCollisionQueryParams QueryParams(FName(TEXT("RV_TRACE")), true, this);
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = false;
		QueryParams.bIgnoreTouches = true;

		FVector const& Start = FirstPersonCamera->GetComponentLocation();
		FVector const& End = Start + (FirstPersonCamera->GetForwardVector() * m_DistanceTrace); 
	
		if (GetWorld()->SweepSingleByChannel(GrabResults, Start, End, FQuat::Identity, COLLISION_PHYSICS_HANDLE, FCollisionShape::MakeSphere(flinteract_sphere_radius) , QueryParams))
		{	
			#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
			DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 2.0f);
			DrawDebugSphere(GetWorld(), End, flinteract_sphere_radius, 32, FColor::Cyan, false, 2.0f);
			#endif
			
			UPrimitiveComponent* ComponentToGrab = GrabResults.GetComponent();

			if(!ComponentToGrab) return;
			FBoxSphereBounds3d Bounds = ComponentToGrab->Bounds;
			FVector const& CentreComponent = Bounds.Origin;
			FVector const& GrabLocation = CentreComponent;
			FRotator const& Rotator = ComponentToGrab->GetComponentRotation();
			
		 	const TArray<FName>& PhyTags = GrabResults.Component->ComponentTags;  
			for (const FName& ComponentTags : PhyTags)
			{
				if (array_grab_name.Contains(ComponentTags))
				{
					
					if (ComponentToGrab->GetMass() <= m_MaxGrabMassObject && ComponentToGrab->IsSimulatingPhysics())
					{
						if (CharacterSound.IsValidIndex(1) && CharacterSound[1] != nullptr)
						{
							UGameplayStatics::PlaySoundAtLocation(this, CharacterSound[1], GetActorLocation());	
							PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, GrabLocation, Rotator);
						}
					}
				}

			}
		}
	}
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

void AMyCharacter::ReleaseComponent() const
{
	PhysicsHandle->ReleaseComponent();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

void AMyCharacter::DontInteract() const
{
	if (CharacterSound.IsValidIndex(2) && CharacterSound[2] != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CharacterSound[2], GetActorLocation());	
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

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

void AMyCharacter::SwitchWeapon1()
{
	SwitchWeaponType(EWeaponType::SMG1);

}

void AMyCharacter::SwitchWeapon2()
{
	SwitchWeaponType(EWeaponType::SHOTGUN);
}

void AMyCharacter::SwitchWeapon3()
{
	SwitchWeaponType(EWeaponType::GRAVITYGUN);
}


void AMyCharacter::AddWeaponToInventory(ABaseWeapon* Weapon)
{
	if (Weapon && !Weapons.Contains(Weapon))
	{
		Weapons.Add(Weapon);

		if (m_icurrent_weapon_index == -1)
		{
			m_icurrent_weapon_index = 0;
		}
	}
}


void AMyCharacter::RemoveWeapon(ABaseWeapon* Weapon)
{
	Weapons.Remove(Weapon);
	if (Weapons.Num() == 0)
	{
		m_icurrent_weapon_index = -1;
	}
	
}


void AMyCharacter::SwitchWeapon(int32 Index)
{
	if (Index >= 0 && Index <= Weapons.Num())
	{
		m_icurrent_weapon_index = Index;
		
		for(int32 i = 0; i < Weapons.Num(); ++i)
		{
			Weapons[i]->SetActorHiddenInGame(i != m_icurrent_weapon_index);
		}
	}
	
	
}

void AMyCharacter::SwitchWeaponType(EWeaponType WeaponType)
{
	int32 Index = static_cast<int32>(WeaponType);
	SwitchWeapon(Index);
	
}









