// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PlayerComponent/FlashLightComponent.h"
#include "Property/damageable.h"
#include "Shared/PlayerTrigger.h"
#include "MyCharacter.generated.h"


//-----------------------------------------------------------------------------
// Forward declarations: 
//-----------------------------------------------------------------------------
class UInputAction;
class UInputMappingContext;
class USkeletalMeshComponent;
class UCameraComponent;
class USoundBase;
class UFlashLightComponent;
class UPhysicsHandleComponent;
class UHealthComponent;
class UCostumeComponent;
class ABaseWeapon;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogCharacterResouce, Log, All)


enum class EWeaponType // SwitchWeapon
{
	SMG1		 UMETA(DisplayName = "Smg1"),
	SHOTGUN	     UMETA(DisplayName = "Smg1"),
	GRAVITYGUN	 UMETA(DisplayName = "Smg1"),

};

UCLASS(Config = Game)
class JOBSGAME_API AMyCharacter : public ACharacter, public IPlayerTrigger, public Idamageable
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = PhysicsHandleComponent, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandle;
	
	UPROPERTY(EditAnywhere, Category = FlashLight, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFlashLightComponent> FlashLightComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = RayCast, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> RayCastCapsule;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
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

	UPROPERTY(EditDefaultsOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Switch1Action;	

	UPROPERTY(EditDefaultsOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Switch2Action;	

	UPROPERTY(EditDefaultsOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Switch3Action;	

	
	#pragma endregion


public:
	
	AMyCharacter();

	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual FString GetPlayer() const override;	

	virtual void   HandleDamage(int32 damage_amounth, EDamageType DamageType) override;

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

	void TickPhysicsHandle() const;

public:
	
	// Animation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool					m_HasRifle;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bhasRifle);

	TObjectPtr<USkeletalMeshComponent> GetMesh1P() const;
	TObjectPtr<UCameraComponent> GetFirstPersonCamera() const;


	int32  GetPlayerHealth() const;
	int32  GetPlayerMaxHealth() const;
	bool   ISDead() const;
	
	float GetMaxSpeedWalk() const;
	float GetMaxSpeedRun() const;
	float GetMaxSpeedCrouch() const;
	float GetMaxAcceleration() const;
	float GetAirControl() const;
	float GetGravityScale() const;
	float GetMaxSpeedFly() const;
	float GetJumpHeight() const;
	float GetMassCombine() const;
	float GetDistanceTrace() const;
	float GetMaxGrabMassObject() const;
	float GetTrowImpulse() const;

	void SetMaxSpeedWalk(float fl_MaxSpeedWalk);
	void SetMaxSpeedRun(float fl_MaxSpeedRun);
	void SetMaxSpeedCrouch(float fl_MaxSpeedCrouch);
	void SetMaxAcceleration(float fl_MaxAcceleration);
	void SetGravityScale(float fl_GravityScale);
	void SetAirControl(float fl_AirControl);
	void SetMaxSpeedFly(float fl_MaxSpeedFly);
	void SetMassCombine(float fl_MassCharacter);
	void SetJumpHeight(float fl_JumpHeight);
	void SetDistanceTrace(float fl_DistanceTrace);
	void SetMaxGrabMassObject(float fl_MaxGrabMassObject);
	void SetTrowImpulse(float fl_TrowImpulse);
	void   SetMaxPlayerHealth(int32 maxplayer_health);
	
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
	void SwitchWeapon1();
	void SwitchWeapon2();
	void SwitchWeapon3();
	
	#pragma endregion

	void   GrabComponent();
	void   ReleaseComponent() const;
	void   DontInteract() const;
	void   SoundResourceLoad();
	void   AddWeaponToInventory(ABaseWeapon* Weapon);
	void   RemoveWeapon(ABaseWeapon* Weapon);
	void   SwitchWeapon(int32 Index);
	void   SwitchWeaponType(EWeaponType WeaponType);
	void   Dead();
	bool   RestoreHealth(int32 HealthAmounth);
	bool   RestoreSuit(int32 SuitAmounth);
	
private:

	FString strPlayerName; 
	
	float	m_MaxSpeedWalk;
	float	m_MaxSpeedRun;
	float	m_MaxSpeedCrouch;
	float	m_MaxAcceleration;        
	float	m_GravityScale;
	float	m_AirControl;
	float	m_MaxSpeedFly;
	float	m_MassCharacter;
	float	m_JumpHeight;
	float	m_DistanceTrace;
	float	m_MaxGrabMassObject;	
	float	m_TrowImpulse;
	
	
	     bool		m_blsDead;
	     bool    m_blsGrabProduct;
	     bool   bls_discharger_suit;
	
	 int32		m_icurrent_weapon_index;
	 int32		m_icurrent_health;
	 int32		m_imaxhealth;
	 int32      m_icharger_suit;
	 int32      m_maxcharger_suit;
	 int32      m_idamageSave;
	
	// Audio my Character
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TArray<USoundBase*> CharacterSound;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<ABaseWeapon*> Weapons;

	


};

FORCEINLINE FString AMyCharacter::GetPlayer() const
{
	return strPlayerName;
}

FORCEINLINE float AMyCharacter::GetMaxSpeedWalk() const
{
    return m_MaxSpeedWalk;
}

FORCEINLINE float AMyCharacter::GetMaxSpeedRun() const
{
    return m_MaxSpeedRun;
}

FORCEINLINE float AMyCharacter::GetMaxSpeedCrouch() const
{
    return m_MaxSpeedCrouch;
}

FORCEINLINE float AMyCharacter::GetMaxAcceleration() const
{
    return m_MaxAcceleration;
}

FORCEINLINE float AMyCharacter::GetAirControl() const
{
    return m_AirControl;
}

FORCEINLINE float AMyCharacter::GetGravityScale() const
{
    return m_GravityScale;
}

FORCEINLINE float AMyCharacter::GetMaxSpeedFly() const
{
    return m_MaxSpeedFly;
}

FORCEINLINE float AMyCharacter::GetJumpHeight() const
{
    return m_JumpHeight;
}

FORCEINLINE float AMyCharacter::GetMassCombine() const
{
    return m_MassCharacter;
}

FORCEINLINE float AMyCharacter::GetDistanceTrace() const
{
    return m_DistanceTrace;
}

FORCEINLINE float AMyCharacter::GetMaxGrabMassObject() const
{
    return m_MaxGrabMassObject;
}

FORCEINLINE float AMyCharacter::GetTrowImpulse() const
{
    return m_TrowImpulse;
}

FORCEINLINE void AMyCharacter::SetMaxSpeedWalk(float fl_MaxSpeedWalk)
{
    m_MaxSpeedWalk = fl_MaxSpeedWalk;
}

FORCEINLINE void AMyCharacter::SetMaxSpeedRun(float fl_MaxSpeedRun)
{
    m_MaxSpeedRun = fl_MaxSpeedRun;
}

FORCEINLINE void AMyCharacter::SetMaxSpeedCrouch(float fl_MaxSpeedCrouch)
{
    m_MaxSpeedCrouch = fl_MaxSpeedCrouch;
}

FORCEINLINE void AMyCharacter::SetMaxAcceleration(float fl_MaxAcceleration)
{
    m_MaxAcceleration = fl_MaxAcceleration;
}

FORCEINLINE void AMyCharacter::SetGravityScale(float fl_GravityScale)
{
    m_GravityScale = fl_GravityScale;
}

FORCEINLINE void AMyCharacter::SetAirControl(float fl_AirControl)
{
    m_AirControl = fl_AirControl;
}

FORCEINLINE void AMyCharacter::SetMaxSpeedFly(float fl_MaxSpeedFly)
{
    m_MaxSpeedFly = fl_MaxSpeedFly;
}

FORCEINLINE void AMyCharacter::SetMassCombine(float fl_MassCharacter)
{
    m_MassCharacter = fl_MassCharacter;
}

FORCEINLINE void AMyCharacter::SetJumpHeight(float fl_JumpHeight)
{
    m_JumpHeight = fl_JumpHeight;
}

FORCEINLINE void AMyCharacter::SetDistanceTrace(float fl_DistanceTrace)
{
    m_DistanceTrace = fl_DistanceTrace;
}

FORCEINLINE void AMyCharacter::SetMaxGrabMassObject(float fl_MaxGrabMassObject)
{
    m_MaxGrabMassObject = fl_MaxGrabMassObject;
}

FORCEINLINE void AMyCharacter::SetTrowImpulse(float fl_TrowImpulse)
{
    m_TrowImpulse = fl_TrowImpulse;
}

FORCEINLINE bool AMyCharacter::GetHasRifle()
{
	return m_HasRifle;
}

FORCEINLINE void AMyCharacter::SetHasRifle(bool bhasRifle)
{
	m_HasRifle = bhasRifle;
}

FORCEINLINE TObjectPtr<USkeletalMeshComponent> AMyCharacter::GetMesh1P() const
{
	return Mesh1P;
}

FORCEINLINE TObjectPtr<UCameraComponent> AMyCharacter::GetFirstPersonCamera() const
{
	return FirstPersonCamera;
}

FORCEINLINE int32 AMyCharacter::GetPlayerHealth() const
{
	return  m_icurrent_health;
}

FORCEINLINE int32 AMyCharacter::GetPlayerMaxHealth() const
{
	return m_imaxhealth;
}

FORCEINLINE bool AMyCharacter::ISDead() const
{
	return m_blsDead;
}

FORCEINLINE void AMyCharacter::SetMaxPlayerHealth(int32 maxplayer_health)
{
	m_imaxhealth = maxplayer_health;
}




