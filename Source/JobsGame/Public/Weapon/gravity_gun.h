// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "gravity_gun.generated.h"
class AMyCharacter;
class UPhysicsHandleComponent;
class USoundBase;
class UCustomDamage;
class UInputMappingContext;
class UInputAction;

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOBSGAME_API Ugravity_gun : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintType, Category = "MechanicsPhysics", meta=(AllowPrivateAccess = "true"))		
	TObjectPtr<UPhysicsHandleComponent> MechanicsPhysics;
	// Input
	UPROPERTY(EditAnywhere, Category = "Input", meta=(AllowPrivateAccess = "true"))		
	TObjectPtr<UInputMappingContext> WeaponMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input", meta=(AllowPrivateAccess = "true"))		
	TObjectPtr<UInputAction> GrabAction;
	UPROPERTY(EditAnywhere, Category = "Input", meta=(AllowPrivateAccess = "true"))		
	TObjectPtr<UInputAction> ReleaseAction;

public:	

	Ugravity_gun();

protected:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AMyCharacter* Character);

	void	PhysicsGrab();
	void	PhysicsInteract();
	void	Trow();
	void	ReleaseObject();
	void	PhysicsTickUpdate();

private:

	FTimerManager		m_InteractTimer;
	float				m_flImpulce;
	float				m_MaxDistance;
	float				m_PhyDamage;						
	
	UPROPERTY(NotBlueprintable)
	TObjectPtr<AMyCharacter> BaseCharacter;
	UPROPERTY()
	TObjectPtr<UCustomDamage> CustomDamage;

};
