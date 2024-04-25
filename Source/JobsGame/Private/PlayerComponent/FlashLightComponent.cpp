// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerComponent/FlashLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

DEFINE_LOG_CATEGORY(LogFlashLight);

void UFlashLightComponent::BeginPlay()
{
	Super::BeginPlay();
	this->SetVisibility(false);
	
	const FSoftObjectPath FindSound(TEXT("/Game/Sound/ActorSound/Cue/flashlight_Cue"));
	TObjectPtr<USoundBase> SoundBase = nullptr;

	if (FindSound.IsValid())
	{
		SoundBase = Cast<USoundBase>(FindSound.TryLoad());
	}
	if (SoundBase != nullptr)
	{
		FlashLightSound = SoundBase;
	}
	else
	{
		UE_LOG(LogFlashLight, Warning, TEXT("Error Loaded: %s"), *FindSound.ToString());
	}	


}


void UFlashLightComponent::ToggleFlashLight()
{
	blsFlashVisible = this->IsVisible();

	if (blsFlashVisible && FlashLightSound != nullptr)
	{
		this->SetVisibility(false);
		UGameplayStatics::PlaySoundAtLocation(this, FlashLightSound, GetComponentLocation());
	}
	else
	{
		this->SetVisibility(true);
		UGameplayStatics::PlaySoundAtLocation(this, FlashLightSound, GetComponentLocation());
	}
	
}

