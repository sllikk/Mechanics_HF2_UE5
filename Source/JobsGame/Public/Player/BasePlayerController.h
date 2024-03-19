// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Logging/LogMacros.h"
#include "BasePlayerController.generated.h"
class UInputMappingContext;

DECLARE_LOG_CATEGORY_EXTERN(BASE_CONTROLLER, Log, All);


UCLASS()

class JOBSGAME_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMapping;

public:

	virtual void BeginPlay() override;

};
