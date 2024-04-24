// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Logging/LogMacros.h"
#include "Health.generated.h"
class USoundBase;
class AMyCharacter;
class UDamageType;

DECLARE_LOG_CATEGORY_EXTERN(LogHeathComponent, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogHeathResource, Log, All);

UCLASS(Config=Game, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UHealthComponent(const FObjectInitializer& ObjectInitializer);

protected:
	
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundBase*> HealthSound;       


public:
	
	FORCEINLINE float				GetHealth() const						{ return m_flHealth; }
	FORCEINLINE float				GetMaxHealth()const						{ return m_flMaxHealth; }
	FORCEINLINE void				SetHealth(float flHealth)				{ m_flHealth = flHealth; }
	FORCEINLINE void				SetMaxHealth(float flMaxDamage)			{ m_flMaxHealth = flMaxDamage; }						
	FORCEINLINE	bool				IsDead() const							{ return m_blsDead; }
	FORCEINLINE	bool				IsAlive() const							{ return m_blsDead; }
				bool				RestoreHealth(float HealthAmount);
	UFUNCTION()
	void                TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
					  AController* InstigatedBy, AActor* DamageCauser);
protected:

	bool							 m_blsDead;
	float							 m_flMaxHealth;
	float							 m_flHealth;
	
};
