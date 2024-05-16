// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlameBarrel.generated.h"
class UStaticMeshComponent;
class UParticleSystem;
class USphereComponent;  
class USoundBase;

UCLASS()
class JOBSGAME_API AFlameBarrel : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category="StaticMeshComponent", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BarrelMesh; 

	UPROPERTY(EditAnywhere, Category="ParticleComponent", meta = (AllowPrivateAccess = "true"))
	TArray<UParticleSystem*> ParticleSystem;
	
	UPROPERTY(EditAnywhere, Category="Overlap", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Trigger;
	
public:	
	// Sets default values for this actor's properties
	AFlameBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//	UFUNCTION()
//	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void			Detected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void			TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
						  AController* InstigatedBy, AActor* DamageCauser);
	
	
	virtual void	EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	
public:	

	void BarrelBurns();
	void Explode();
	
private:

	float Health;
	FTimerHandle TimerExplode;
	
};

