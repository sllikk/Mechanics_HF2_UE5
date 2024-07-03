// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"
class UStaticMeshComponent;
class UStaticMesh;
class USphereComponent;	
class USoundBase;
class AMyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickupDelegat);

UCLASS()
class JOBSGAME_API AItemBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "StaticMeshComponent", meta=(AllowPrivateAccess = "true")) 
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;

	UPROPERTY(EditAnywhere, Category = "BoxComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> TriggerCollision;

	UPROPERTY(EditAnywhere, Category = "BoxComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> TouchSound;	


public:
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnTouch(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void Use(AActor* pCharacterUse);

	UPROPERTY(BlueprintAssignable)
	FOnPickupDelegat PickupDelegat;
	
public:
	
	TObjectPtr<UStaticMeshComponent> GetBaseStaticMeshComponent() const;
	TObjectPtr<USoundBase>           GetSoundTouch() const;
	TObjectPtr<USphereComponent>        GetTriggerCollision() const;
	float   GetMassObj() const;
	float	GetSphereRadius() const;
	bool    IsUse() const;

	
	void	SetBaseStaticMeshComponent(UStaticMeshComponent* pStaticMeshComponent);
	void	SetSoundTouchSound(USoundBase* pSoundBase);
	void    SetMassObj(float flmass);
	void    SetRadiusSphere(float flsphere_radius);
	void    SetUse(bool bls_stat_use);	
	
private:

	float	flmassObj;
	float	flradius_sphere;	
	bool 	bls_use;


};

/*
 Getter Setter
 */
FORCEINLINE TObjectPtr<UStaticMeshComponent> AItemBase::GetBaseStaticMeshComponent() const
{
	return BaseMeshComponent;
}

FORCEINLINE void AItemBase::SetBaseStaticMeshComponent(UStaticMeshComponent* pStaticMeshComponent)
{
	BaseMeshComponent = pStaticMeshComponent;
}

FORCEINLINE void AItemBase::SetSoundTouchSound(USoundBase* pSoundBase)
{
	TouchSound = pSoundBase;
}

FORCEINLINE void AItemBase::SetMassObj(float flmass)
{
	flmassObj = flmass;
}

FORCEINLINE float AItemBase::GetMassObj() const
{
	return flmassObj;
}

FORCEINLINE float AItemBase::GetSphereRadius() const
{
	return flradius_sphere;
}

FORCEINLINE void AItemBase::SetRadiusSphere(float flsphere_radius)
{
	flradius_sphere = flsphere_radius;
}

FORCEINLINE bool AItemBase::IsUse() const
{
	return bls_use;	
}

FORCEINLINE void AItemBase::SetUse(bool bls_stat_use)
{
	bls_use = bls_stat_use;
}

FORCEINLINE TObjectPtr<USoundBase> AItemBase::GetSoundTouch() const
{
	return TouchSound;
}

FORCEINLINE TObjectPtr<USphereComponent> AItemBase::GetTriggerCollision() const
{
	return TriggerCollision;
}
