// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/supply_crate.h"

#include "GeometryCollection/GeometryCollectionComponent.h"

Asupply_crate::Asupply_crate()
{
	SupplyCrateGeometry = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	RootComponent = SupplyCrateGeometry;

	SetGeometryCollectionComponet(SupplyCrateGeometry);

	LoadGeometry("/Game/GC/GC_SupplyCrate");
	
	LoadFieldComponent("/Game/GC/Impact");
	

}


void Asupply_crate::BeginPlay()
{
	Super::BeginPlay();

	SetMaxHealth(25.0f);
	SetMassProps(45.0f);
	SetMinSpeedForDestruction(5000000.0f);
	SupplyCrateGeometry->SetNotifyRigidBodyCollision(true);
}


void Asupply_crate::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void Asupply_crate::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

}


void Asupply_crate::PhysicsDestroy(FVector DestroyLocation)
{
	Super::PhysicsDestroy(DestroyLocation);


}


void Asupply_crate::ApplyDamage(float Damage, FVector HitLocation)
{
	Super::ApplyDamage(Damage, HitLocation);
}
