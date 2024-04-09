// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PhysicsHandle.generated.h"
class AMyCharacter;
class UInputAction;
class USoundBase;

DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsHandle, Log, All);

UCLASS(Config = Game, ClassGroup= (Custom), meta=(BlueprintSpawnableComponent))
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
	static void TrowObject();
	static void DontInteract();
	
	FORCEINLINE	 virtual void ReleaseComponent() override;		
	FORCEINLINE	virtual void GrabComponents();

	
private:
	// Config variables
	UPROPERTY(Config)
	bool blsSoftAngularConstraint = true;
	UPROPERTY(Config)
	bool blsSoftLinearConstraint = true;
	UPROPERTY(Config)
	bool blsInterpolateTarget = true;
	UPROPERTY(Config)
	float m_LinearDamping = 200.0f;
	UPROPERTY(Config)
	float m_LinearStiffness = 750.0f;
	UPROPERTY(Config)
	float m_AngularDamping = 500.0f;
	UPROPERTY(Config)
	float m_AngularStiffness = 1500.0f;
	UPROPERTY(Config)
	float m_InterpolationSpeed = 50.0f;
	UPROPERTY(Config)
	float m_DistanceTrace = 190.0f;
	UPROPERTY(Config)
	float m_TrowImpulce = 225.0f;
	
private:

	TObjectPtr<AMyCharacter> Character;
	
};
