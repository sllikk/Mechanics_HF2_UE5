// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shared/PropsDamage.h"
#include "DestructionProps.generated.h"
class UGeometryCollectionComponent;
class USoundBase; 

UCLASS()
class JOBSGAME_API ADestructionProps : public AActor, public IPropsDamage 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UGeometryCollectionComponent> GeometryCollectionComponent;

	UPROPERTY(EditAnywhere, Category = "Spawning", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AActor> SpawnFieldDestruction;
	
public:	

	ADestructionProps();

	
protected:
	// Called when the game starts or when spawned
	virtual void	BeginPlay() override;
	// Called every frame
	virtual void	Tick(float DeltaTime) override;
	// HitComponent
	UFUNCTION()
	virtual void	OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void    ApplyDamage(float Damage, FVector HitLocation) override;

public:	
	
	#pragma region GETTER_SETTER

	FORCEINLINE	TObjectPtr<UGeometryCollectionComponent>
		GetGeometryCollectionComponent() const					    { return GeometryCollectionComponent; }

	void SetGeometryCollectionComponet
		(TObjectPtr<UGeometryCollectionComponent> NewGeometry)		{ GeometryCollectionComponent = NewGeometry; }
	
	FORCEINLINE float	GetHealth() const							{ return m_flHealth; }
				void	SetHealth(float fl_health)					{ m_flHealth = fl_health; }

	#pragma endregion 
	
	void SpawnFieldComponent(FVector vecSpawnLocation);
		
	
private:	

	float m_flHealth;

};
