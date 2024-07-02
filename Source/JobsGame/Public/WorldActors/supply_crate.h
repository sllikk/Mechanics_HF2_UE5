// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/DestructionProps.h"
#include "supply_crate.generated.h"
class UGeometryCollectionComponent;

UCLASS()
class JOBSGAME_API Asupply_crate : public ADestructionProps
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Destruction", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UGeometryCollectionComponent> SupplyCrateGeometry;

	
public:
 
	Asupply_crate();


protected:	

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void PhysicsDestroy(FVector DestroyLocation) override;

	virtual void ApplyDamage(float Damage, FVector HitLocation) override;

	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent*
		OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	
public:

 	FORCEINLINE void SpawnSupply(FVector vecSpawn) const;
	
};
