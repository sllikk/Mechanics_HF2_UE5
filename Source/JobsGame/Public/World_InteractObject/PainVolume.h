// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PainCausingVolume.h"
#include "PainVolume.generated.h"
class UDamageType;
class AController;
class USoundBase;

DECLARE_LOG_CATEGORY_EXTERN(LogPainCausing, Log, All);

USTRUCT()
struct FLoadSound
{
	GENERATED_BODY()

	UPROPERTY()
	FString ResourcePath;
	UPROPERTY()
	TObjectPtr<UObject> LoadResource;

	FLoadSound(){};

	FLoadSound(const FString& NameResource, TObjectPtr<UObject> resource)
	:ResourcePath(NameResource), LoadResource(resource){}
};

UCLASS()
class JOBSGAME_API APainVolume : public APainCausingVolume
{
	GENERATED_BODY()

	/** Whether volume currently causes damage. */
	UPROPERTY(EditAnywhere, Category=PainCausingVolume)
	uint16 PainCausing:1;

	/** Damage done per second to actors in this volume when bPainCausing=true */
	UPROPERTY(EditAnywhere, Category=PainCausingVolume)
	float DamagePerSecond;

	/** Type of damage done */
	UPROPERTY(EditAnywhere, Category=PainCausingVolume)
	TSubclassOf<UDamageType> DamageTypes;

	/** If pain causing, time between damage applications. */
	UPROPERTY(EditAnywhere, Category=PainCausingVolume)
	float PainIntervals;

	/** if bPainCausing, cause pain when something enters the volume in addition to damage each second */
	UPROPERTY(EditAnywhere, Category=PainCausingVolume)
	uint16 blsEntryPain:1;

	/** Checkpointed bPainCausing value */
	UPROPERTY()
	uint16 BACKUP_bPainCausings:1;

	/** Controller that gets credit for any damage caused by this volume */
	UPROPERTY()
	TObjectPtr<AController> DamageInstigators;

	/** Sound arrays */
	UPROPERTY(EditDefaultsOnly, Category=Sound)
	TArray<USoundBase*> FireSound;
	
	/**Particle effect */ 
	UPROPERTY(EditDefaultsOnly, Category=Sound)
	TObjectPtr<UParticleSystem> FireParticle;	

public:

	APainVolume(const FObjectInitializer& ObjectInitializer);

protected:

	void CausePainTo(class AActor* Other);

	FTimerHandle TimerHandle_PainTimer;
	
public:

	virtual void PainTimer() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
		
	virtual void PostInitializeComponents() override;
	
	void ActorEnteredVolume(AActor* Other);

	void BeginPlay() override;

};
