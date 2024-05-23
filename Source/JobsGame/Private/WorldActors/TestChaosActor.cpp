// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/TestChaosActor.h"

#include "GeometryCollection/GeometryCollectionComponent.h"
#include "PhysicsField/PhysicsFieldComponent.h"

// Sets default values
ATestChaosActor::ATestChaosActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PhysicsFieldComponent = CreateDefaultSubobject<UPhysicsFieldComponent>(TEXT("Destruction"));
	GeometryCollectionComponent = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GC"));
	RootComponent = GeometryCollectionComponent; 

	MaxHealth = 25.0f;

}

// Called when the game starts or when spawned
void ATestChaosActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestChaosActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATestChaosActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Урон на основе импульса столкновения
	float Damage = NormalImpulse.Size() * 0.01f; // Настройте коэффициент урона по своему усмотрению
	ApplyDamage(Damage, Hit.ImpactPoint);
}


void ATestChaosActor::ApplyDamage(float Damage, FVector HitDamage)
{
	MaxHealth -= Damage;
	if (MaxHealth <= 0.0f)
	{
		DestroyBox(HitDamage);
	}
}


void ATestChaosActor::DestroyBox(FVector HitLocation)
{
	if (GeometryCollectionComponent)
	{
	//	GeometryCollectionComponent->ApplyBreakDamage(1.0f, HitLocation, 1000.0f);
	}
}

