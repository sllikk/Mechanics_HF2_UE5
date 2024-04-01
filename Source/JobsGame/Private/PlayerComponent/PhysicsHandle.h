// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Player/MyCharacter.h"
#include "PhysicsHandle.generated.h"
class AMyCharacter;
class USoundBase;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsHandle, Log, All);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UPhysicsHandle : public UPhysicsHandleComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "MappingContext", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> PhysicsHandleMappingContext;	
	
	UPROPERTY(EditAnywhere, Category = "InputAction", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ToggleGrabAction; 

	UPROPERTY(EditDefaultsOnly, Category = "InputAction", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TrowAction;
	
public:	

	UPhysicsHandle();
	
protected:

	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION()
	void AttachToPhysicsHandleController(AMyCharacter* TargetCharacter);
	
	void ToggleGrabObject();
	void TrowObject();
	void ReleaseComponent() override;		
	void GrabComponents();
	void DontInteract();

private:

	UPROPERTY(NotBlueprintType)
	TObjectPtr<AMyCharacter> Character;
	
};
