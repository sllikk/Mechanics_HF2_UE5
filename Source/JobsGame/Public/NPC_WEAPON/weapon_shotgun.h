// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC_WEAPON/BaseWeapon.h"
#include "weapon_shotgun.generated.h"
class USkeletalMeshComponent;

UCLASS()
class JOBSGAME_API Aweapon_shotgun : public ABaseWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> shotgun_mesh;
	
public:
	// Sets default values for this actor's properties
	Aweapon_shotgun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Fire() override;
	
public:

	

};
