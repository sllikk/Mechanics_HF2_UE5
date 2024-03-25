// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Logging/LogMacros.h"
#include "HopperMine.generated.h"
class AMyCharacter;
class UStaticMeshComponent;
class USoundBase;
class USphereComponent;
class UPointLightComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogLoadResourceMine, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogHopper, Log, All);

USTRUCT(NotBlueprintable)
struct FLoadSoundResource
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly)
	FString ResourcePath;
	UPROPERTY(VisibleAnywhere)
	UObject* LoadedResource;
};

UENUM(BlueprintType)
enum EStatMine : uint8
{
	ACTIVATE UMETA(DisplayName = "Activate"),
	DEACTIVATE UMETA(DisplayName = "Deactivate"),
	ATTACK UMETA(DisplayName = "Attack"),
	DEPLOY UMETA(DisplayName = "Deploy"),
	ATTACH_TO_SURFACE UMETA(DisplayName = "Attach to surface"),
};

UCLASS(Config = Game)
class JOBSGAME_API AHopperMine : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> HopperMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "SphereComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> DetectedSphere;

	
	//UPROPERTY(EditDefaultsOnly, Category = "SphereComponent", meta=(AllowPrivateAccess = "true"))
	//TObjectPtr<USphereComponent> ActiveSphere;

	UPROPERTY(EditAnywhere, Category = "LightComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> LightDetector;
	
public:	
	
	AHopperMine();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION(CallInEditor)
	void OnDetectionRadiusBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(CallInEditor)
	void OnDetectionRadiusEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
public:	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual  void ActivateMine();
	
private:

	TObjectPtr<AMyCharacter> MyCharacter;
	EStatMine StatMine;

	
};

