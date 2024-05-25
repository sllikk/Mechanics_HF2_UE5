// Fill out your copyright notice in the Description page of Project Settings.

#include "Shared/DestructionProps.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Hearing.h"

DEFINE_LOG_CATEGORY(LogDestructionProps)

// Sets default values
ADestructionProps::ADestructionProps()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; 
	
	GeometryCollectionComponent = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollectionComponent"));
	RootComponent = GeometryCollectionComponent;
	
}

// Called when the game starts or when spawned
void ADestructionProps::BeginPlay()
{
	Super::BeginPlay();

	// Broadcast hit delegate
	GeometryCollectionComponent->OnComponentHit.AddDynamic(this, &ADestructionProps::OnComponentHit);
	// Simulate physics and physics property
	GeometryCollectionComponent->SetSimulatePhysics(true);	   	
	GeometryCollectionComponent->SetMassOverrideInKg(NAME_Actor, GetMassProps(), true);
	
}

// Called every frame
void ADestructionProps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*--------------------------------------------------------------------------------------------------------------------------------------*/

void ADestructionProps::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp != nullptr)
	{
		// Calculate the velocity of the hitting object at the point of impact
		FVector VelocityAtImpact = OtherComp->GetComponentVelocity();

		// Calculate the speed of the hitting object at the point of impact
		float SpeedAtImpact = VelocityAtImpact.Size();

		//Kinetic energy of the hitting object
		float KineticEnergy = 0.5f * OtherComp->GetMass() * SpeedAtImpact * SpeedAtImpact;

		// Use SpeedAtImpact or KineticEnergy to determine if the hit was strong enough to trigger destruction
		if (KineticEnergy > GetMinSpeedForDestruction())
		{
			PhysicsDestroy();
		}

		if (GetSpawn())
		{
			GeometryCollectionComponent->OnComponentHit.RemoveAll(this);
		}
	}
	
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/

void ADestructionProps::ApplyDamage(float Damage, FVector HitLocation)
{
	// Take Damage
	m_flHealth = FMath::Clamp(GetHealth() - Damage, 0.0f, GetMaxHealth());

	// Destroy hit object
	if (GetHealth() <= 0)
	{
		PhysicsDestroy();
	}

}
/*--------------------------------------------------------------------------------------------------------------------------------------*/


void ADestructionProps::SpawnFieldComponent(FVector vecSpawnLocation)
{
	// Spawn MasterField Blueprint
	FActorSpawnParameters SpawnParams;
	const TObjectPtr<AActor> Spawn = GetWorld()->SpawnActor<AActor>(SpawnFieldDestruction, vecSpawnLocation, FRotator::ZeroRotator, SpawnParams);
	// Set spawn for destroy
	SetSpawn(true);

	if (Spawn)
	{
		SetLifeSpan(0.5);	// Life Span MasterField And Destroy	
	}
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/


void ADestructionProps::PhysicsDestroy()
{
	if (GeometryCollectionComponent)
	{
		SpawnFieldComponent(GeometryCollectionComponent->Bounds.Origin);
	}
	
}
/*--------------------------------------------------------------------------------------------------------------------------------------*/
// Emit AI noise for NPC hearing
void ADestructionProps::EmitAINoise() const
{

}

// Load Destroy Geometry
void ADestructionProps::LoadGeometry(const FString& Path) const
{
	const FSoftObjectPath FindGeometry(*Path);
	static TObjectPtr<UGeometryCollection> Geometry = nullptr;

	if (FindGeometry.IsValid())
	{
		Geometry = Cast<UGeometryCollection>(FindGeometry.TryLoad());
	}
	if (Geometry != nullptr)
	{
		// Set Load Geometry
		GeometryCollectionComponent->SetRestCollection(Geometry);
	}
	else
	{
		// mb error log
		UE_LOG(LogDestructionProps, Warning, TEXT("Error Load: %s"), *FindGeometry.ToString())
	}
	
}

void ADestructionProps::LoadFieldComponent(const FString& Path)
{
	static ConstructorHelpers::FClassFinder<AActor> ClassFinder(*Path);

	if (ClassFinder.Succeeded())
	{
		SpawnFieldDestruction = ClassFinder.Class;
	}
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

void ADestructionProps::Debug()
{
}

