// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Mode.h"

AGame_Mode::AGame_Mode() 
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnFinder(TEXT("/Game/FirstPerson/Blueprints/BP_Character"));
	
	if (PlayerPawnFinder.Succeeded())
	{
		DefaultPawnClass = PlayerPawnFinder.Class;
	}

}

