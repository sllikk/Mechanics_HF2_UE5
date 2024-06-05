// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/supply_crate.h"

#include "GeometryCollection/GeometryCollectionComponent.h"
#include "WorldActors/BatteryKit.h"
#include "WorldActors/HealthKit.h"

Asupply_crate::Asupply_crate()
{
	SupplyCrateGeometry = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	RootComponent = SupplyCrateGeometry;

	SupplyCrateGeometry->ComponentTags.Add("Destruction");

	SetGeometryCollectionComponet(SupplyCrateGeometry);

	LoadGeometry("/Game/GC/GC_SupplyCrate");
	
	LoadFieldComponent("/Game/GC/Impact");
	// Обновление навигационных данных
}


void Asupply_crate::BeginPlay()
{
	Super::BeginPlay();

	SetMaxHealth(25.0f);

	SetMassProps(45.0f);

	SetMinSpeedForDestruction(50000000.0f);

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

	SpawnSupply(SupplyCrateGeometry->Bounds.Origin);
}


void Asupply_crate::ApplyDamage(float Damage, FVector HitLocation)
{
	Super::ApplyDamage(Damage, HitLocation);
}


void Asupply_crate::SpawnSupply(FVector vecSpawn)
{
	int8 MAXSPAWN = 2;
	TArray<TSubclassOf<AActor>> Classes;
	Classes.Add(ABatteryKit::StaticClass());
	Classes.Add(AHealthKit::StaticClass());

	for(int8 i = 0; i < MAXSPAWN; i++)
	{
		if (Classes.Num() > 0)
		{
			int8 ItemIndex = FMath::RandRange(0, Classes.Num() - 1);
			TSubclassOf<AActor> ItemClass = Classes[ItemIndex];	

			FActorSpawnParameters ActorSpawnParameters;
			GetWorld()->SpawnActor<AActor>(ItemClass, vecSpawn, FRotator::ZeroRotator);	
		}
	}
}