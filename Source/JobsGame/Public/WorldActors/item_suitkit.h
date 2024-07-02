// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldActors/ItemBase.h"
#include "item_suitkit.generated.h"
class AMyCharacter;

UCLASS()
class JOBSGAME_API Aitem_suitkit : public AItemBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> suitkit_mesh;

	
public:

	Aitem_suitkit();

protected:	

	virtual void BeginPlay() override;
	virtual void Use(AActor* pCharacterUse) override;
	virtual void OnTouch(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
private:

	UPROPERTY()
	TObjectPtr<AMyCharacter> ptrPlayer;

	
};
