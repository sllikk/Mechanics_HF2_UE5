// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseGameUI.generated.h"
class UTextBlock;

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
	
protected:

	void UpdateHealthHud(int32 update_health) const;
	void UpdateSuitHud(int32 update_suit) const;

};
