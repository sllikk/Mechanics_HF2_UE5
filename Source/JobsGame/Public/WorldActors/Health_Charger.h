// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shared/interact.h"
#include "Health_Charger.generated.h"
class AMyCharacter;
class UStaticMeshComponent;
class UPointLightComponent;
class USoundBase;

DECLARE_LOG_CATEGORY_EXTERN(LogHealthCharger, Log, All);

UCLASS(Config=Game)
class JOBSGAME_API AHealth_Charger : public AActor, public Iinteract
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category="MeshComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> HealthChargerMeshComponent;
	
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
	virtual void				Interact(AActor* Actor) override;
			void				DebugStation() const;	
			void				StartRestore(AActor* Actor);
			void				StopRestore();
			void				RestoreCharge(AActor* Actor);

private:
		// Sound
		UPROPERTY(VisibleAnywhere, Category = "SoundLoad")
		TArray<USoundBase*> Health_ChargerSound;
		UPROPERTY(VisibleAnywhere, Category = "SoundLoad")
		TArray<UAudioComponent*> AudioComponents;
	
		FTimerHandle	 HealthRestoreTimer;
		float			 m_flMaxCharger;
		float			 m_flCharger;
		float            m_flInteractCharacter;
		bool			 m_blsDischarged;
		bool			 bls_Interact;
	
	
};
