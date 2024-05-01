// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/gravity_gun.h"
#include "Player/MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"

Ugravity_gun::Ugravity_gun()
{

}


	
void Ugravity_gun::BeginPlay()
{
	Super::BeginPlay();
	m_MaxDistance = 500;
	SetWorldScale3D(FVector(6.0f,6.0f,6.0f));


}

void Ugravity_gun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void Ugravity_gun::AttachWeapon(AMyCharacter* Character)
{
	BaseCharacter = Character;

	if (BaseCharacter == nullptr || BaseCharacter->GetHasRifle())
	{
		return;
	}

	// Attach GravityGun to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(BaseCharacter->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	BaseCharacter->SetHasRifle(true);
	
	// Input
	if (const APlayerController* PlayerController = Cast<APlayerController>(BaseCharacter->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			PlayerSubsystem->AddMappingContext(WeaponMappingContext, 1);
		}
		if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			check(Input);
			Input->BindAction(GrabAction, ETriggerEvent::Started,this, &Ugravity_gun::PhysicsGrab);
			Input->BindAction(GrabAction, ETriggerEvent::Completed,this, &Ugravity_gun::ReleaseObject);
			Input->BindAction(GrabAction, ETriggerEvent::Started,this, &Ugravity_gun::Trow);
		}
	}
	
}


void Ugravity_gun::PhysicsGrab()
{
	UE_LOG(LogActor, Warning, TEXT("Pressed!!!!"));	
	
	FHitResult GrabResult;
	const FCollisionQueryParams QueryParams;
	FVector const& Start = GetSocketLocation("Muzzle");
	FVector const& End = Start + BaseCharacter->GetFirstPersonCamera()->GetForwardVector() + m_MaxDistance;
	
	GetWorld()->LineTraceSingleByChannel(GrabResult, Start, End, ECC_GameTraceChannel3, QueryParams);
	
	UPrimitiveComponent* ComponentTOGrab = GrabResult.GetComponent();
	

}


void Ugravity_gun::PhysicsInteract()
{

}

void Ugravity_gun::Trow()
{

}


void Ugravity_gun::ReleaseObject()
{

}

void Ugravity_gun::PhysicsTickUpdate()
{

}
