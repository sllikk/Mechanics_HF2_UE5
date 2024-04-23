// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "GameFramework/Character.h"
#include "PlayerComponent/FlashLightComponent.h"
#include "Shared/interact.h"
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

// Load Sound resource for Character 
USTRUCT()
struct FResourceSound
{
	GENERATED_BODY()
	UPROPERTY(NotBlueprintable)
	FString  ResourcePath;
	UPROPERTY(NotBlueprintable)
	TObjectPtr<UObject> LoadResource;

	FResourceSound() { }	
	FResourceSound(const FString& InResourcePath, UObject* ObjectLoad)
		:ResourcePath(InResourcePath), LoadResource(ObjectLoad){}

};


UCLASS(Config = Game)
class JOBSGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = PhysicsHandleComponent, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandle;
	
	UPROPERTY(EditAnywhere, Category = FlashLight, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFlashLightComponent> FlashLightComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RayCast, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> RayCastCapsule;	
	
	// ActorsComponents
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;
	
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

public:
	
	//Return object
	FORCEINLINE	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	FORCEINLINE	UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCamera; }

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
	void GrabComponent();
	void ReleaseComponent();
	void DontInteract();
	void TrowObject();
	bool interact;
	
	#pragma endregion

private:

	#pragma region Default_Character_Settings

	UPROPERTY(Config)
	float m_MaxSpeedWalk = 500.0f;
	UPROPERTY(Config)
	float m_MaxSpeedRun = 700.0f;
	UPROPERTY(Config)
	float m_MaxSpeedCrouch = 400.0f;
	UPROPERTY(Config)
	float m_MaxAcceleration = 2048.0f;        
	UPROPERTY(Config)
	float m_GravityScale = 1.0f;
	UPROPERTY(Config)
	float m_AirControl = 0.8f;
	UPROPERTY(Config)
	float m_MaxSpeedFly = 200.0f;
	UPROPERTY(Config)
	float m_MassCharacter = 20.0f;
	UPROPERTY(Config)
	float m_JumpHeight = 300.0f;
	UPROPERTY(Config)
	float m_LineTraceLength = 180.0f;
	UPROPERTY(Config)
	float m_DistanceTrace = 190;
	UPROPERTY(Config)
	float m_MaxGrabMassObject = 80;	
	UPROPERTY(Config)
	float m_TrowImpulse = 250;

	#pragma endregion
	
	// Audio my Character
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USoundBase> SoundBase;
	
	
	bool blsDoorInteract;


};

