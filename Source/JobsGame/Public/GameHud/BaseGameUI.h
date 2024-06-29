// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerComponent/Health.h"
#include "BaseGameUI.generated.h"
class UTextBlock;
class UHealthComponent;

UCLASS(Abstract)
class JOBSGAME_API UBaseGameUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UTextBlock> HealthBlock;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UTextBlock> SuitBlock;
	
public:
	
	virtual void NativeConstruct() override;
	
public:

	UFUNCTION()
	void UpdateHealthHud(int32 update_health);
	UFUNCTION()
	void UpdateSuitHud(int32 update_suit) const;


private:
	UPROPERTY()
	UHealthComponent* PlayerHealthComponent;
};
