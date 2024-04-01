// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerComponent/PhysicsHandle.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
DEFINE_LOG_CATEGORY(LogPhysicsHandle);

UPhysicsHandle::UPhysicsHandle()
{
}


void UPhysicsHandle::BeginPlay()
{
	Super::BeginPlay();
	

}


void UPhysicsHandle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UPhysicsHandle::AttachToPhysicsHandleController(AMyCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	FString CharacterName = Character->GetName();
	
	if (Character == nullptr)
	{
		return;
	}
	else
	{
		UE_LOG(LogPhysicsHandle, Warning, TEXT("%s: nullptr and return PhysicsHandle"), *CharacterName)
	}
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputComponent* InputComponents = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			if (UEnhancedInputComponent* EnhancedInput = dynamic_cast<UEnhancedInputComponent*>(InputComponents))
			{
				EnhancedInput->BindAction(TrowAction, ETriggerEvent::Started, this, &UPhysicsHandle::TrowObject);
				EnhancedInput->BindAction(TrowAction, ETriggerEvent::Started, this, &UPhysicsHandle::ToggleGrabObject);
			}
			else
			{
				UE_LOG(LogPhysicsHandle, Warning, TEXT("Eror input PhysicsHandle"));
			}
		
		}
	}

}

void UPhysicsHandle::ToggleGrabObject()
{
}

void UPhysicsHandle::TrowObject()
{
}

void UPhysicsHandle::ReleaseComponent()
{
	Super::ReleaseComponent();
}

void UPhysicsHandle::GrabComponents()
{
}

void UPhysicsHandle::DontInteract()
{
}
