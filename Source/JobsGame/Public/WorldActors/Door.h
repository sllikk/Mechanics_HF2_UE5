// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Logging/LogMacros.h"
#include "Components/TimelineComponent.h"
#include "Door.generated.h"
class UStaticMeshComponent;
class UBoxComponent;
class USoundBase;
class UCurveFloat;
class AMyCharacter;
struct FTimeline;

DECLARE_LOG_CATEGORY_EXTERN(LOG_LOADING_RESOURCE, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogDoor, Log, All);

UCLASS()
class JOBSGAME_API ADoor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = "StaticMesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DoorComponent;
	
	UPROPERTY(EditInstanceOnly, Category = "StaticMesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DoorFrameComponent;

	//UPROPERTY(EditInstanceOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UBoxComponent> BoxCollision;

	
public:	
	
	ADoor();

protected:
	
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	
	void Interact();

	TObjectPtr<AMyCharacter> Character;
	
public:	
	
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> OpenDoorSound;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> CloseDoorSound;

private:

	UPROPERTY(EditDefaultsOnly, Category = "CurveFloat")
	TObjectPtr<UCurveFloat> CurveFloat;

	UFUNCTION(BlueprintCallable)
	void OpenDoor(float Value);

	UFUNCTION(BlueprintCallable)
	void DoorOnsameSide();

	FTimeline Timeline;
	bool blsDoorClossed;
	bool blsDoorOnsameSide;
	float m_DoorRotateAngle = 90.0f;

private:	


	
};

// Struct load to resource in object 
struct FInfoLoadResourse
{
	FString ResourceLoadPath; 
	UObject* LoadingResource;
};
