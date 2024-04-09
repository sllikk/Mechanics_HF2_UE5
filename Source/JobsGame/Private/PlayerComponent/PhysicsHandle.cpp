// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerComponent/PhysicsHandle.h"
#include "Camera/CameraComponent.h"
#include "Player/MyCharacter.h"

DEFINE_LOG_CATEGORY(LogPhysicsHandle)

UPhysicsHandle::UPhysicsHandle()
{

	bInterpolateTarget = blsInterpolateTarget;
	bSoftAngularConstraint = blsSoftAngularConstraint;
	bSoftLinearConstraint = blsSoftLinearConstraint;
	LinearDamping = m_LinearDamping;
	LinearStiffness = m_LinearStiffness;
	AngularDamping = m_AngularDamping;
	AngularStiffness = m_AngularStiffness;
	InterpolationSpeed = m_InterpolationSpeed;
	

}


void UPhysicsHandle::BeginPlay()
{
	Super::BeginPlay();
	

}


void UPhysicsHandle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GrabbedComponent)
	{
		FVector const& Start = Character->FirstPersonCamera->GetComponentLocation();		
		FVector const& NewLocation = Start + Character->FirstPersonCamera->GetForwardVector() * m_DistanceTrace; 
		FRotator const& NewRotator = Character->FirstPersonCamera->GetComponentRotation();
		SetTargetLocationAndRotation(NewLocation, NewRotator);
	}
}


void UPhysicsHandle::ToggleGrabObject()
{
	if (GrabbedComponent)
	{
		ReleaseComponent();
	}
	else
	{
		GrabComponents();
	}
	
}


void UPhysicsHandle::TrowObject()
{
}


void UPhysicsHandle::GrabComponents()
{
	if (Character->FirstPersonCamera == nullptr)return;
	{
		FHitResult GrabResult;
		FCollisionQueryParams QueryParams(TEXT("RV_TRACE"), false, Character);
		FVector const& Start = Character->FirstPersonCamera->GetComponentLocation();
		FVector const& End = Start + Character->FirstPersonCamera->GetForwardVector() * m_DistanceTrace;

		if (GetWorld()->LineTraceSingleByChannel(GrabResult, Start, End, ECC_GameTraceChannel2, QueryParams))
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
			DrawDebugPoint(GetWorld(), Start, 20, FColor::Red, false);
			DrawDebugPoint(GetWorld(), End, 20, FColor::Red, false);		

			UPrimitiveComponent* ComponentToGrab = GrabResult.GetComponent();
			if (!ComponentToGrab)return;
			if (ComponentToGrab->IsSimulatingPhysics() || ComponentToGrab->GetMass() <= 0)
			{
				DontInteract();
				return;
			}
						
			FBoxSphereBounds Bounds = ComponentToGrab->Bounds;
			FVector const& CentreToComponent = Bounds.Origin;
			FVector const& GrabLocation = CentreToComponent;
			FRotator GrabRotation = ComponentToGrab->GetComponentRotation();

			if (ComponentToGrab->GetMassScale() >= 60)
			{
				GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, GrabLocation, GrabRotation);
			}

		}
		else
		{
			DontInteract();
		}
	}
	

}


void UPhysicsHandle::ReleaseComponent()
{ 
	Super::ReleaseComponent();

}


void UPhysicsHandle::DontInteract()
{
	UE_LOG(LogPhysicsHandle, Warning, TEXT("DontInteract!!!!!!!!!"));
}
