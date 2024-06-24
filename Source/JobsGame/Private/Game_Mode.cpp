// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Mode.h"

#include "Kismet/GameplayStatics.h"
#include "Property/ImpactEffectHandler.h"

AGame_Mode::AGame_Mode() 
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnFinder(TEXT("/Game/FirstPerson/Blueprints/BP_Character"));
	
	if (PlayerPawnFinder.Succeeded())
	{
		DefaultPawnClass = PlayerPawnFinder.Class;
	}

}


void AGame_Mode::BeginPlay()
{
	Super::BeginPlay();


}


void AGame_Mode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	
}


void AGame_Mode::Spawn() const
{
}

void AGame_Mode::SpawnObjectPool()
{

}

