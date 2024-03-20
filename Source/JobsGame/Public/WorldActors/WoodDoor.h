// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Logging/LogMacros.h"
#include "Components/TimelineComponent.h"
#include "WoodDoor.generated.h"
class AMyCharacter;
class UStaticMeshComponent;
class UBoxComponent;
class UCurveFloat;
class USoundBase;
struct FTimeline;

DECLARE_LOG_CATEGORY_EXTERN(LogWoodDoor, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogLoandingResource, Log, All);

UCLASS()
class JOBSGAME_API AWoodDoor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleInstanceOnly, Category = "StaticMesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> DoorComponent;

	UPROPERTY(VisibleInstanceOnly, Category = "StaticMesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> DoorFrameComponent;

	UPROPERTY(VisibleInstanceOnly, Category = "StaticMesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> BoxCollision;

public:	

	AWoodDoor();

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<AMyCharacter> Character;


protected:
	
	virtual void BeginPlay() override;


public:	
	
	virtual void Tick(float DeltaTime) override;
	
	void Interact();

public:

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> OpenDoorSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> CloseDoorSound;


private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCurveFloat> CurveFloat;

	FTimeline Timeline;

	void OpenDoor(float Value);
	void DoorOnsameSide();

	bool m_blsDoorClossed;
	bool m_blsDoorOnsameSide;
	float m_DoorRotateAngle = 90.0f;


};
