// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/ItemBase.h"
#include "Shared/PlayerTrigger.h"
#include "Components/BoxComponent.h"


// Sets default values
AItemBase::AItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseStaticMesh"));
	RootComponent = BaseMeshComponent;
	
	TriggerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTriggerComponent"));
	TriggerCollision->SetCollisionProfileName(TEXT("Interaction"));
	TriggerCollision->SetupAttachment(BaseMeshComponent);	
	
	flmassObj = 10.0f;
	bls_use = false;
}


// Called when the game starts or when spawned
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
		PickupDelegat.Broadcast();
		Use(OtherActor);
		if (bls_use == true)
		{
			TriggerCollision->OnComponentBeginOverlap.RemoveAll(this);
			this->Destroy();	
		}
	}	
	
}


void AItemBase::Use(AActor* pCharacter)
{

}



