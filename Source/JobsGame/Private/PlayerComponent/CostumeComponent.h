// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Logging/LogMacros.h"
#include "CostumeComponent.generated.h"
class USoundBase;

DECLARE_LOG_CATEGORY_EXTERN(LogCostumeComponent, Log, All);

UCLASS()
class UCostumeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UCostumeComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charger")
	float m_CurrentChargerCostume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Charger")
	float m_MaxChargerCostume;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:

	UFUNCTION(BlueprintCallable)
	bool RestoreCharger(float Amounth);

	UFUNCTION(BlueprintCallable)
	 void CostumeDischarged();

	UFUNCTION()
	virtual void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);


private:

	bool m_blsDischargerCostume;

};
