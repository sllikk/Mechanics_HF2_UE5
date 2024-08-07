// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC_WEAPON/BaseWeapon.h"
#include "weapon_smg1.generated.h"
class USkeletalMeshComponent;
class AShell;
class UArrowComponent;
class Aobject_pool;

UCLASS()
class JOBSGAME_API Aweapon_smg1 : public ABaseWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> smg1_mesh;

	UPROPERTY(EditAnywhere, Category="Shell", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AShell> shelldrops;

	UPROPERTY(EditAnywhere, Category="Arrow", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> SpawnShellArrow;
	
public:

	Aweapon_smg1();
	
protected:

	virtual void	BeginPlay() override;
	virtual void	Tick(float DeltaSeconds) override;
	virtual void	PrimaryAttack() override;
	virtual void	StartAttack() override;
	virtual void	StopAttack() override;
	
private:

	UPROPERTY()
	TArray<AActor*> PoolArray;

 	//void Debug() const;
	
};
