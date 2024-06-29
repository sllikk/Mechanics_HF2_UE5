// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHud/BaseGameUI.h"
#include "Components/TextBlock.h"
#include "Player/MyCharacter.h"

void UBaseGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	
	

	
}

void UBaseGameUI::UpdateHealthHud(int32 update_health) 
{
	if (HealthBlock)
	{
		HealthBlock->SetText(FText::AsNumber(update_health));
	}
}

void UBaseGameUI::UpdateSuitHud(int32 update_suit) const
{
	if (SuitBlock)
	{
		SuitBlock->SetText(FText::AsNumber(update_suit));
	}
	
}
