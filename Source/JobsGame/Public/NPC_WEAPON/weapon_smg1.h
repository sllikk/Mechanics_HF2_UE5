// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC_WEAPON/BaseWeapon.h"
#include "weapon_smg1.generated.h"
class USkeletalMeshComponent;
class AShell;
class UArrowComponent;

UCLASS()
class JOBSGAME_API Aweapon_smg1 : public ABaseWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> smg1_mesh;

	UPROPERTY(EditAnywhere, Category="Shell", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AShell> shelldrops;

	UPROPERTY(EditAnywhere, Category="Arrow", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> SpawnShellArrow;

	//UPROPERTY(EditAnywhere, Category="Pooling", meta=(AllowPrivateAccess = "true"))
	
	
public:

	Aweapon_smg1();
	
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PrimaryAttack() override;
	virtual void Interact(AActor* Actor) override;
	virtual void ApplyDamage(float Damage, FVector HitLocation) override;
	virtual void PhysicsTraceLogic(const FHitResult& HitResult) override;
	virtual void StartAttack() override;
	virtual void StopAttack() override;

public:

	void SpawnShell() const;
	
private:

	float			FireRate;
	FTimerHandle	FireTimerHandle;
	uint8			iWeaponCallFlag;

	
};
