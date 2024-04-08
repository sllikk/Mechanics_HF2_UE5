// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PhysicsHandle.generated.h"
class AMyCharacter;
class UInputAction;
class USoundBase;


DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsHandle, Log, All);

UCLASS(ClassGroup= (Custom), meta=(BlueprintSpawnableComponent))
class JOBSGAME_API UPhysicsHandle : public UPhysicsHandleComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ToggleGrabAction; 

	UPROPERTY(EditDefaultsOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TrowAction;

public:

	UPhysicsHandle();

protected:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:

	void ToggleGrabObject();
	void TrowObject();
	void DontInteract();
	
	FORCEINLINE	 virtual void ReleaseComponent() override;		
	FORCEINLINE	virtual void GrabComponents();

	
private:


	
};
