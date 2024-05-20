// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/PickUp.h"

#include "NPC_WEAPON/gravity_gun.h"


// Sets default values
APickUp::APickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Grab_Sphere = CreateDefaultSubobject<Ugrab_sphere>(TEXT("Grab_Sphere"));
	RootComponent = Grab_Sphere;
	Gravity_Gun = CreateDefaultSubobject<Ugravity_gun>(TEXT("Gravity_gun"));
	Gravity_Gun->SetupAttachment(Grab_Sphere);
	
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

