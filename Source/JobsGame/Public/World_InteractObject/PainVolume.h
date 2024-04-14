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
