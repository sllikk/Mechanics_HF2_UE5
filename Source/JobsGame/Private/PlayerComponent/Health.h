// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Logging/LogMacros.h"
#include "Property/CustomDamageType.h"
#include "Health.generated.h"
class USoundBase;
class AMyCharacter;
class UCustomDamageType;
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
	
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CurrrentHealth)
	float m_CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MaxHealth)
	float m_MaxHealth;


	
protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundBase*> HealthSound;       

	
public:

	UFUNCTION(Blueprintable)
	bool RestoreHealth(float HealthAmount);

	UFUNCTION(Blueprintable)
	void IsDead();
	
	UFUNCTION(Blueprintable)
	virtual void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                        class AController* InstigatedBy, AActor* DamageCauser);


protected:

	void FireDamage(float Damage, FDamageTypeData& DamageTypeData);
	void ElectricalDamage(float Damage, FDamageTypeData& DamageTypeData);
	void FallDamage(float Damage, FDamageTypeData& DamageTypeData);
	void PhysicsDamage(float Damage, FDamageTypeData& DamageTypeData);
	void ExplosionDamage(float Damage, FDamageTypeData& DamageTypeData);
	
private:

	bool m_blsDead;
	
	

};
