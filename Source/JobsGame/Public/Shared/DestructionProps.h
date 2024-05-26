// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shared/PropsDamage.h"
#include "DestructionProps.generated.h"
class UGeometryCollectionComponent;
class USoundBase; 

DECLARE_LOG_CATEGORY_EXTERN(LogDestructionProps, Log, All);

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

	virtual void	Debug() override;
	
public:	
	
	#pragma region GETTER_SETTER

	FORCEINLINE	TObjectPtr<UGeometryCollectionComponent>
		GetGeometryCollectionComponent() const					    { return GeometryCollectionComponent; }

	FORCEINLINE	void SetGeometryCollectionComponet
		(TObjectPtr<UGeometryCollectionComponent> NewGeometry)		{ GeometryCollectionComponent = NewGeometry; }
	
	FORCEINLINE float	GetHealth() const							 { return m_flHealth; }
	FORCEINLINE float	GetMaxHealth() const						 { return m_flMaxHealth; }
	FORCEINLINE	void	SetMaxHealth(float fl_health)				 { m_flHealth = fl_health; }
	FORCEINLINE float   GetMinSpeedForDestruction() const			 { return m_flMinSpeedForDestruction; }		
	FORCEINLINE	void	SetMinSpeedForDestruction(float flmin_speed) { m_flMinSpeedForDestruction = flmin_speed; }	
	FORCEINLINE bool	GetSpawn() const							 { return blsSpawn; }
	FORCEINLINE	void    SetSpawn(bool bspawn_stat)					 { blsSpawn = bspawn_stat; }	
	FORCEINLINE float   GetMassProps() const						 { return m_flMassProps; }	
	FORCEINLINE void    SetMassProps(float flmass)					 { m_flMassProps = flmass; } 
	
	#pragma endregion 

		virtual void	PhysicsDestroy(FVector DestroyLocation);
				void	SpawnFieldComponent(FVector vecSpawnLocation);
				void	EmitAINoise() const;
	FORCEINLINE void	LoadGeometry(const FString& Path) const;
 	FORCEINLINE	void	LoadFieldComponent(const FString& Path);

private:	

	float	m_flHealth;
	float   m_flMaxHealth;
	float   m_flMinSpeedForDestruction;
	float	m_flMassProps;
	bool	blsSpawn; 
	
};
