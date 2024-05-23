// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestChaosActor.generated.h"
class UPhysicsFieldComponent;
class UGeometryCollectionComponent; 

UCLASS()
class JOBSGAME_API ATestChaosActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Destruction", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UGeometryCollectionComponent> GeometryCollectionComponent;
	
	UPROPERTY(EditAnywhere, Category="Destruction", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPhysicsFieldComponent> PhysicsFieldComponent;
	
public:	
	// Sets default values for this actor's properties
	ATestChaosActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	

	float MaxHealth;
	void ApplyDamage(float Damage, FVector HitDamage);

	void DestroyBox(FVector HitLocation);
};
