// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerComponent/Health.h"
#include "Health_Charger.generated.h"
class AMyCharacter;
class UStaticMeshComponent;
class UBoxComponent;
class UPointLightComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogHealthCharger, Log, All);

UCLASS(Config=Game)
class JOBSGAME_API AHealth_Charger : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category="MeshComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> HealthChargerMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category="MeshComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> LightCharger;
	
public:	

	AHealth_Charger();

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;
	
public:	

	FORCEINLINE	float			GetMaxCharger() const				{ return m_flMaxCharger; }
	FORCEINLINE	float			GetCharge() const				    { return m_flCharger; }
	FORCEINLINE	void			SetMaxCharger(float flChargeMax)	{ m_flMaxCharger = flChargeMax; }
	FORCEINLINE	void			SetCharger(float flCharge)			{ m_flCharger = flCharge; }
				bool            blsCharger;
	UFUNCTION()
	virtual void Interact();
	void DebugStation();


protected:
		FTimerHandle HealthRestoreTimer;
		float		m_flMaxCharger;
		float		m_flCharger;
		bool        m_blsDischarged;
		float  MaxInteractionTime = 1;
		float	DecreaseRate;
public:

	UPROPERTY()
	AMyCharacter* Character;
	UPROPERTY()
	TObjectPtr<UHealthComponent> HealthComponent;
};
