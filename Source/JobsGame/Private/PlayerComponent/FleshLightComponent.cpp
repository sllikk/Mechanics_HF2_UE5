// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerComponent/FleshLightComponent.h"
#include "Player/MyCharacter.h"

DEFINE_LOG_CATEGORY(LogFleshLight)


void UFleshLightComponent::BeginPlay()
{
	Super::BeginPlay();
	this->SetVisibility(false);

}


void UFleshLightComponent::ToggleFleshLight()
{
	blsFleshVisible = this->IsVisible();

	if (blsFleshVisible)
	{
		this->SetVisibility(false);
		UE_LOG(LogFleshLight, Warning, TEXT("Off!!!!!"));
	}
	else
	{
		this->SetVisibility(true);
		UE_LOG(LogFleshLight, Warning, TEXT("On!!!!!"));
	}
	
}

