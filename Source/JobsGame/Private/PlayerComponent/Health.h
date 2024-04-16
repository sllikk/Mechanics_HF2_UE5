// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomType/CustomDamage.h"
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
	
	UFUNCTION()
	virtual void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                        class AController* InstigatedBy, AActor* DamageCauser);


protected:

	 void FireDamage(float Damage, FDamageTypeData& DamageTypeData);
	FORCEINLINE void ElectricDamage(float Damage, const FDamageTypeData& DamageTypeData);
	FORCEINLINE void FallDamage(float Damage, const FDamageTypeData& DamageTypeData);
	FORCEINLINE void DrownDamage(float Damage, const FDamageTypeData& DamageTypeData);
	FORCEINLINE void ExplosionDamage(float Damage, const FDamageTypeData& DamageTypeData);
	FORCEINLINE void PhysicsDamage(float Damage, const FDamageTypeData& DamageTypeData);
	FORCEINLINE void WeaponDamage(float Damage, const FDamageTypeData& DamageTypeData);
	
	
private:

	bool m_blsDead;
	
	

};
