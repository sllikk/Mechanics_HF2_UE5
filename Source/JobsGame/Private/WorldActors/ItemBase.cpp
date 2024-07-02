// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/ItemBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AItemBase::AItemBase() : flmassObj(15), flradius_sphere(100)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseStaticMesh"));
	RootComponent = BaseMeshComponent;
	
	TriggerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTriggerComponent"));
	TriggerCollision->SetCollisionProfileName(TEXT("Interaction"));
	TriggerCollision->InitSphereRadius(flradius_sphere);
	TriggerCollision->SetupAttachment(BaseMeshComponent);	

	
	flmassObj = 10.0f;
	bls_use = false;
}



void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	TriggerCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnTouch);
	BaseMeshComponent->SetSimulatePhysics(true);
	BaseMeshComponent->SetMassOverrideInKg(NAME_Actor, flmassObj);
}


void AItemBase::OnTouch(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		Use(OtherActor);
		UE_LOG( LogCollision, Warning, TEXT("Touch: %s"),*OtherActor->GetClass()->GetName() )
		
		if (bls_use == true)
		{
			PickupDelegat.Broadcast();
			TriggerCollision->OnComponentBeginOverlap.RemoveAll(this);
			this->Destroy();	
		}
	}	
	
}


void AItemBase::Use(AActor* pCharacter)
{
// only virtual
}



