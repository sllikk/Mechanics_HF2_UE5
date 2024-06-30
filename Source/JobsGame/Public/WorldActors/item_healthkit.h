// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerComponent/Health.h"
#include "WorldActors/ItemBase.h"
#include "item_healthkit.generated.h"

UCLASS()
class JOBSGAME_API Aitem_healthkit : public AItemBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> healthkit_mesh;

	
public:

	Aitem_healthkit();

protected:	

	virtual void BeginPlay() override;

	virtual void Use(AActor* pCharacterUse) override;

private:

	UPROPERTY()	
	TObjectPtr<UHealthComponent> HealthComponent;
	
};
