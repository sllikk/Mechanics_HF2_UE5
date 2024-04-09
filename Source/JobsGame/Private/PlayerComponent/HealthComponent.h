// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Logging/LogMacros.h"
#include "HealthComponent.generated.h"
class USoundBase;

DECLARE_LOG_CATEGORY_EXTERN(LogHeathComponent, Log, All);

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
	


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	TObjectPtr<USoundBase> DeadSound;


public:

	UFUNCTION(Blueprintable)
	bool RestoreHealth(float HealthAmount);

	UFUNCTION(Blueprintable)
	void IsDead();
		
	UFUNCTION()
	virtual void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);

private:

	bool m_blsDead;


};
