// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/MyCharacter.h"
#include "gravity_gun.generated.h"
class USoundBase;
class UPhysicsHandleComponent;
class UInputAction;
class UInputMappingContext;
class USphereComponent;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOBSGAME_API Ugravity_gun : public USkeletalMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="PhysicsHandle", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPhysicsHandleComponent> Gravity_Physics;
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> GrabAction;
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TrowAction;

	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> WeaponMappingContext;
	
	
	
public:

	Ugravity_gun();

protected:

	void			BeginPlay() override;
	void			TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void	EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachToWeapon(AMyCharacter* TargetCharacter);

	// Input 
	void					Gravity_Grab(void);
	void					Gravity_Trow(void);
	void					Gravity_Realese(void);
	void					PhysicsTick() const;
	void					TrowImpulce();
	//----------------------Getter Setter--------------------------------------------------------

	FORCEINLINE float		GetPhyscanon_Maxmass() const						{ return m_flphyscanon_maxmass; }
	FORCEINLINE void        SetPhyscanon_Maxmass(float MaxMass)					{ m_flphyscanon_maxmass = MaxMass; }
	FORCEINLINE void		SetPhyscannonTraceLength(float TraceLength)			{ m_flphyscanon_tracelength = TraceLength; }
	FORCEINLINE float		GetPhyscannonTraceLength() const					{ return m_flphyscanon_tracelength; }
	FORCEINLINE void		SetPhyscannonPullForce(float PullForce)				{ m_flphyscannon_pullforce = PullForce; }
	FORCEINLINE float		GetPhyscannonPullForce() const						{ return m_flphyscannon_pullforce; }
	FORCEINLINE void		SetPhyscannonMinForce(float MinForce)				{ m_flphyscannon_minforce = MinForce; }
	FORCEINLINE float		GetPhyscannonMinForce() const						{ return m_flphyscannon_minforce; }
	FORCEINLINE void		SetPhyscannonMaxForce(float MaxForce)				{ m_flphyscannon_maxforce = MaxForce; }
	FORCEINLINE float		GetPhyscannonMaxForce() const						{ return m_flphyscannon_maxforce; }
	FORCEINLINE float		GetTraceSphereRadius() const						{ return m_trace_sphere_radius; }	
	FORCEINLINE float       GetTraceSphereHalfHeight() const					{ return m_trace_sphere_halfheight; }
	
private:

	UPROPERTY()
	AMyCharacter* Character;       // Player
	UPROPERTY()
	TArray<FName> ComponentTag;    // Tag GrabComponent
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> CurrentPulledComponent = nullptr;
	
	float		m_flphyscanon_maxmass;        // Sets the maximum mass at which an object can be picked up  
	float		m_flphyscanon_tracelength;     // How far an object can be pulled
	float		m_flphyscannon_pullforce;         // How much force to be used when pulling objects to the player
	float		m_flphyscannon_minforce;
	float		m_flphyscannon_maxforce;
	float		m_trace_sphere_radius;
	float		m_trace_sphere_halfheight;
	bool		bIsPullingObject;


};
