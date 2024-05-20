// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/MyCharacter.h"
#include "gravity_gun.generated.h"
class USoundBase;
class UPhysicsHandleComponent;
class UInputAction;
class UInputMappingContext;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOBSGAME_API Ugravity_gun : public USkeletalMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="PhysicsHandle", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPhysicsHandleComponent> Gravity_Physics;
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> GrabAction;
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TrowAction;

	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> WeaponMappingContext;

	
public:

	Ugravity_gun();

protected:

	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
public:

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachToWeapon(AMyCharacter* TargetCharacter);

	void Gravity_Grab(void);
	void Gravity_Trow(void);
	void Gravity_Realese(void);
private:

	UPROPERTY()
	AMyCharacter* Character;
	
};
