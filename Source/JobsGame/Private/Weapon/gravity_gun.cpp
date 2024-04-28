// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/gravity_gun.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"

Agravity_gun::Agravity_gun()
{
	PrimaryActorTick.bCanEverTick = true;

	GravityGunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = GravityGunMesh;

	MechanicsPhysics = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

}

void Agravity_gun::BeginPlay()
{
	Super::BeginPlay();
	
}

void Agravity_gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

