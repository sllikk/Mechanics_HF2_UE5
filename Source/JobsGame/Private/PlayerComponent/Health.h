// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Logging/LogMacros.h"
#include "Property/damageable.h"
#include "Health.generated.h"
class USoundBase;
class AMyCharacter;

DECLARE_LOG_CATEGORY_EXTERN(LogHeathComponent, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogHeathResource, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthUpdate, int32, newhealth);

UCLASS(Config=Game, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UHealthComponent : public UActorComponent, public Idamageable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundBase*> HealthSound;       


public:	
	
	UHealthComponent(const FObjectInitializer& ObjectInitializer);

protected:
	
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

			int32  GetPlayerHealth() const;
			int32  GetPlayerMaxHealth() const;
			bool   ISDead() const;
			bool   RestoreHealth(int32 HealthAmounth);
			void   SetMaxPlayerHealth(int32 maxplayer_health);
	virtual void   HandleDamage(int32 damage_amounth, EDamageType DamageType) override;
			void   Dead();
private:

	bool		m_blsDead;
	int32		icurrent_health;
	int32		imaxhealth;
	
};

FORCEINLINE int32 UHealthComponent::GetPlayerHealth() const
{
	return  icurrent_health;
}

FORCEINLINE int32 UHealthComponent::GetPlayerMaxHealth() const
{
	return imaxhealth;
}

FORCEINLINE bool UHealthComponent::ISDead() const
{
	return m_blsDead;
}

FORCEINLINE void UHealthComponent::SetMaxPlayerHealth(int32 maxplayer_health)
{
	imaxhealth = maxplayer_health;
}
