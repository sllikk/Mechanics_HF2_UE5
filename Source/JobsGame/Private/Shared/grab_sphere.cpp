// Fill out your copyright notice in the Description page of Project Settings.


#include "grab_sphere.h"

#include "NPC_WEAPON/BaseWeapon.h"


// Sets default values for this component's properties
Ugrab_sphere::Ugrab_sphere()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void Ugrab_sphere::BeginPlay()
{
	Super::BeginPlay();

	this->OnComponentBeginOverlap.AddDynamic(this, &Ugrab_sphere::OnSphereBeginOverlap);
	
}


// Called every frame
void Ugrab_sphere::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void Ugrab_sphere::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
		if (Character != nullptr)
		{
			PicUp.Broadcast(Character);
			OnComponentBeginOverlap.RemoveAll(this);
		}
	}
	
}

