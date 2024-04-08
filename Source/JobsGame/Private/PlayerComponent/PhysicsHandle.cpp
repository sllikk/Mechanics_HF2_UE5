// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerComponent/PhysicsHandle.h"
	
DEFINE_LOG_CATEGORY(LogPhysicsHandle)

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
