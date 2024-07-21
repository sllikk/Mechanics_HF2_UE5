// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "npc_turret_floor.generated.h"

class UPointLightComponent;
class UPoseableMeshComponent;
class USoundBase;


enum EDetectedState
{
	TURRET_EYE_SEE_TARGET,			//Sees the target, bright and big
	TURRET_EYE_SEEKING_TARGET,		//Looking for a target, blinking (bright)
	TURRET_EYE_DORMANT,				//Not active
	TURRET_EYE_DEAD,				//Completely invisible
	TURRET_EYE_DISABLED,			//Turned off, must be reactivated before it'll deploy again (completely invisible)
	TURRET_EYE_ALARM,				// On side, but warning player to pick it back up
};

UCLASS(Blueprintable)
class JOBSGAME_API Anpc_turret_floor : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPoseableMeshComponent> turret_mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> detected_light;

	UPROPERTY(EditAnywhere, Category="Sound", meta=(AllowPrivateAccess = "true"))
	TArray<USoundBase*> TurretSound;
	
public:
	// Sets default values for this pawn's properties
	Anpc_turret_floor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

public:

	FORCEINLINE UPoseableMeshComponent* GetPoseableMesh() const { return turret_mesh; }
	
	void LightUpdate(EDetectedState DetectedState);
	
	
private:	

};
