// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "GameFramework/Character.h"
#include "PlayerComponent/FlashLightComponent.h"
#include "GenericTeamAgentInterface.h"
#include "MyCharacter.generated.h"
class UInputAction;
class UInputMappingContext;
class USkeletalMeshComponent;
class UCameraComponent;
class USoundBase;
class UFlashLightComponent;
class UPhysicsHandleComponent;
class UHealthComponent;
class UCostumeComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogCharacterResouce, Log, All)


UCLASS(Config = Game)
class JOBSGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	#pragma region SubObject

	
	UPROPERTY(EditAnywhere, Category = PhysicsHandleComponent, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandle;
	
	UPROPERTY(EditAnywhere, Category = FlashLight, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFlashLightComponent> FlashLightComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RayCast, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> RayCastCapsule;	
	
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;
	
	#pragma endregion 

	
	#pragma region INPUT

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FlashLightAction;	

	UPROPERTY(EditDefaultsOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> GrabAction;	

	UPROPERTY(EditDefaultsOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TrowAction;	

	#pragma endregion


public:
	
	AMyCharacter();

	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

	void TickPhysicsHandle() const;

public:
	
	#pragma region Getters_Setters
	// Animation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool					m_HasRifle;
	UFUNCTION(BlueprintCallable, Category=Weapon)
	bool					GetHasRifle()					{ return m_HasRifle; }
	UFUNCTION(BlueprintCallable, Category=Weapon)
	void					SetHasRifle(bool bhasRifle)		{ m_HasRifle = bhasRifle; }
	          
	FORCEINLINE	USkeletalMeshComponent*		GetMesh1P() const								 { return Mesh1P; }
	FORCEINLINE	UCameraComponent*			GetFirstPersonCamera() const					 { return FirstPersonCamera; }

	FORCEINLINE float						GetMaxSpeedWalk() const							 { return m_MaxSpeedWalk; }
	FORCEINLINE void						SetMaxSpeedWalk(float fl_MaxSpeedWalk)			 { m_MaxSpeedWalk = fl_MaxSpeedWalk; }
	FORCEINLINE float						GetMaxSpeedRun() const							 { return m_MaxSpeedRun; }
	FORCEINLINE void						SetMaxSpeedRun(float fl_MaxSpeedRun)		 	 { m_MaxSpeedRun = fl_MaxSpeedRun; }
	FORCEINLINE float						GetMaxSpeedCrouch() const						 { return m_MaxSpeedCrouch; }
	FORCEINLINE void						SetMaxSpeedCrouch(float fl_MaxSpeedCrouch)		 { m_MaxSpeedCrouch = fl_MaxSpeedCrouch; }
	FORCEINLINE	float						GetMaxAcceleration() const						 { return m_MaxAcceleration; }
	FORCEINLINE	void						SetMaxAcceleration(float fl_MaxAcceleration)	 { m_MaxAcceleration =  fl_MaxAcceleration; } 
	FORCEINLINE	float						GetGravityScale() const							 { return m_GravityScale; }
	FORCEINLINE	void						SetGravityScale(float fl_GravityScale)		 	 { m_GravityScale = fl_GravityScale; }
	FORCEINLINE	float						GetAirControl() const							 { return m_AirControl; }
	FORCEINLINE	void						SetAirControl(float fl_AirControl)				 { m_AirControl = fl_AirControl; }
	FORCEINLINE	float						GetMaxSpeedFly() const							 { return m_MaxSpeedFly; }
	FORCEINLINE	void						SetMaxSpeedFly(float fl_MaxSpeedFly)			 { m_MaxSpeedFly = fl_MaxSpeedFly; }
	FORCEINLINE	float						GetMassCharacter() const						 { return m_MassCharacter; }
	FORCEINLINE	void						SetMassCharacter(float fl_MassCharacter)	 	 { m_MassCharacter = fl_MassCharacter; }
	FORCEINLINE	float						GetJumpHeight() const						  	 { return m_JumpHeight; }
	FORCEINLINE	void						SetJumpHeight(float fl_JumpHeight)				 { m_JumpHeight = fl_JumpHeight; }
	FORCEINLINE	float						GetDistanceTrace() const						 { return m_DistanceTrace; }
	FORCEINLINE	void						SetDistanceTrace(float fl_DistanceTrace)	     { m_DistanceTrace = fl_DistanceTrace; }
	FORCEINLINE	float						GetMaxGrabMassObject() const					 { return m_MaxGrabMassObject; }
	FORCEINLINE	void						SetMaxGrabMassObject(float fl_MaxGrabMassObject) { m_MaxGrabMassObject = fl_MaxGrabMassObject; }
	FORCEINLINE	float						GetTrowImpulse() const							 { return m_TrowImpulse; }
	FORCEINLINE	void						SetTrowImpulse(float fl_TrowImpulse)			 { m_TrowImpulse = fl_TrowImpulse; }
	
	# pragma endregion
	
#pragma region FUNC_INPUT

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Run();
	void StopRun();
	void StartCrouch();
	void StopCrouch();
	void Interact();
	void Flashlight();
	void ToggleGrab();
	void TrowObject();
	
	#pragma endregion

	void GrabComponent();
	void ReleaseComponent() const;
	void DontInteract() const;
	void SoundResourceLoad();
	
private:

	#pragma region Default_Character_Settings

	float	m_MaxSpeedWalk = 500.0f;
	float	m_MaxSpeedRun = 700.0f;
	float	m_MaxSpeedCrouch = 400.0f;
	float	m_MaxAcceleration = 2048.0f;        
	float	m_GravityScale = 1.0f;
	float	m_AirControl = 0.8f;
	float	m_MaxSpeedFly = 200.0f;
	float	m_MassCharacter = 20.0f;
	float	m_JumpHeight = 300.0f;
	float	m_DistanceTrace = 190;
	float	m_MaxGrabMassObject = 80;	
	float	m_TrowImpulse = 250;

	bool    m_blsGrabProduct;

	#pragma endregion
	
	// Audio my Character
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TArray<USoundBase*> CharacterSound;
	
	


};

