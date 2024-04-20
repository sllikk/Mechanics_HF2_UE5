// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere, Category="MeshComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> LightCharger;
	
public:	

	AHealth_Charger();

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	

	FORCEINLINE	float			GetMaxCharger() const				{ return m_flMaxCharger; }
	FORCEINLINE	float			GetCharge() const				    { return m_flCharger; }
	FORCEINLINE	void			SetMaxCharger(float flChargeMax)	{ m_flMaxCharger = flChargeMax; }
	FORCEINLINE	void			SetCharger(float flCharge)			{ m_flCharger = flCharge; }

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	

	
protected:

		float		m_flMaxCharger;
		float		m_flCharger;
		bool        m_blsDischarged;
	
};
