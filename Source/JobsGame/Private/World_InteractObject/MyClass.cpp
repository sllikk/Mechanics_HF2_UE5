// Fill out your copyright notice in the Description page of Project Settings.


#include "MyClass.h"

#include "Player/MyCharacter.h"

// Sets default values for this component's properties
UMyClass::UMyClass()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UMyClass::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UMyClass::OnSphereBeginOverlap);	
	
	
}

void UMyClass::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);

	if (Character != nullptr)
	{
		PickUp.Broadcast(Character);

		OnComponentBeginOverlap.RemoveAll(this);
	}
	

}



