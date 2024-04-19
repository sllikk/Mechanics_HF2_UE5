// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Logging/LogMacros.h"
#include "Health.generated.h"
class USoundBase;
class AMyCharacter;

DECLARE_LOG_CATEGORY_EXTERN(LogHeathComponent, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogHeathResource, Log, All);

// Load Resource
USTRUCT()
struct FResourceLoad
{
	GENERATED_BODY()

	UPROPERTY(NotBlueprintable)
	FString ResourcePath;
	UPROPERTY(NotBlueprintable)
	TObjectPtr<UObject> LoadResource;

	FResourceLoad() { }	
	FResourceLoad(const FString& InResourcePath, UObject* ObjectLoad)
		:ResourcePath(InResourcePath), LoadResource(ObjectLoad){}
};
	


UCLASS(Config=Game, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UHealthComponent(const FObjectInitializer& ObjectInitializer);

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundBase*> HealthSound;       

	
public:
	
	FORCEINLINE float				GetHealth() const						{ return m_flHealth; }
	FORCEINLINE float				GetMaxHealth()const						{ return m_flMaxHealth; }
	FORCEINLINE void				SetHealth(float flHealth)				{ m_flHealth = flHealth; }
	FORCEINLINE void				SetMaxHealth(float flMaxDamage)			{ m_flMaxHealth = flMaxDamage; }						
	FORCEINLINE	bool				IsDead() const							{ return m_blsDead; }
	FORCEINLINE	bool				IsAlive() const							{ return m_blsliveState; }
			//	bool				RestoreHealth(float HealthAmount);
	// Take damage Character
	virtual void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                        class AController* InstigatedBy, AActor* DamageCauser);

protected:

	bool							 m_blsDead;
	bool							 m_blsliveState;
	float							 m_flMaxHealth;
	UPROPERTY(BlueprintReadOnly, Category= HEALTH)
	float							 m_flHealth;
	
};
