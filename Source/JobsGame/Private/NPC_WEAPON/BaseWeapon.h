// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Player/MyCharacter.h"
#include "Property/damageable.h"
#include "Property/object_pool.h"
#include "Shared/interact.h"
#include "BaseWeapon.generated.h"
class USkeletalMeshComponent;
class USoundBase;
class UInputMappingContext;
class UInputAction;
class Aobject_pool;
class AImpactEffectHandler;

DECLARE_LOG_CATEGORY_EXTERN(LogWeapon, All, Log);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitSurface, const FHitResult&, HitResult);

UCLASS(Blueprintable)
class JOBSGAME_API ABaseWeapon : public AActor, public Iinteract, public Idamageable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> WeaponMappingContext;

	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PrimaryAttackAction;

	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SecondaryAttackAction;
	
	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ReloadAction;
	
	UPROPERTY(EditAnywhere, Category="PoolObject", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<Aobject_pool> pool_object;

	UPROPERTY(EditAnywhere, Category="PoolObject", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<Aobject_pool> pool_object_decal;
	
public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called End Play
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void	SpawnEmitter();

public:

	FORCEINLINE USkeletalMeshComponent* GetWeaponMeshComponent()
	const { return WeaponSkeletalMeshComponent; };

	
	// Methods for getting values
	Aobject_pool* GetShellPool() const;		
	FName GetSocketName() const;
	int32 GetMaxAmmo() const;
	int32 GetCurrentAmmo() const;
	int32 GetInvAmmo() const;
	int32 GetDamageAmounth() const;

		float GetReloadTime() const;
		float GetBulletSpread() const;
		float GetMaxShootDistance() const;
		float GetAttackRate() const;
		float GetMaxPhysicsImpulse() const;

	FVector GetShotForwardVector() const;												// Return forward vector .cpp
	FVector CalculateBulletSpread(const FVector& ShotDirection) const;
	
	// Methods for setting values
	void SetSkeletalMesh(USkeletalMeshComponent* NewMesh);
	void SetMaxShootDistance(float fldistance);
	void SetSocetName(FName newName);
	void SetMaxAmmo(int32 iAmmo);
	void SetCurrentAmmo(int32 iAmmo);
	void SetInvAmmo(int32 i_invammo);
	void SetDamageAmounth(int32 iamounth);
	void SetReloadTime(float flnew_time);
	void SetAttackRate(float fl_rateattack);
	void SetBulletSpread(float flspread);
	void SetPhysicsImpulse(float fl_impulse);

	// Sound effects and load
	 void	SetFireSound(USoundBase* NewSound);				
	 void	SetReloadSound(USoundBase* NewSound);			
	 void	SetMuzzleFlash(UParticleSystem* NewEffect);		

	UFUNCTION(BlueprintCallable)
	FORCEINLINE	void	AttachWeapon(AMyCharacter* Character, const FName& SocketName);

	virtual void		PrimaryAttack();	
	//virtual void SecondaryAttack();
	virtual void		Reload();
	virtual void		Interact(AActor* Actor) override;
	virtual void        HandleDamage(int32 damage_amounth, EDamageType DamageType) override;
	virtual void		StartAttack();
	virtual void		StopAttack();
	virtual void		ShellDrop();
	virtual void		ObjectPoolRelease();	
			void		ConsumeAmmo(int32 iAmmo);
	static  void		EmmiterAINoise();
			void		SpawnDecals(const FHitResult& TraceResult); 
			void        PoolRelease_Decals();	
			void		FinishReload();
			void		PhysicsTraceLogic(const FHitResult& HitResult);
	
private:

	UPROPERTY()	
	TObjectPtr<USoundBase> FireSound;
	UPROPERTY()	
	TObjectPtr<USoundBase> ReloadSound;
	UPROPERTY()
	TObjectPtr<USoundBase> SwitchSound;
	UPROPERTY()
	TObjectPtr<UParticleSystem> MuzzleFlash;
	UPROPERTY(EditAnywhere, Category="Animation")
	TObjectPtr<UAnimMontage> aminPrimaryAttack;
	UPROPERTY()
	TObjectPtr<AMyCharacter> Player;             // Player class for weapon
	
	FTimerHandle ReloadTimer;
	FTimerHandle PrimaryAttackTimer;
	FTimerHandle TimePoolObject;
	FTimerHandle TimePoolObject_Decals;
	
	int32	 icurrentAmmo;
	int32	 imaxAmmo;
	int32	 imaxInventoryAmmo;
	int32    idamage;
	FName	 fSocketName;			// Socket for shoot 

	float	 m_flmaxTraceLength;
	float    m_flBulletSpread; 
	float    m_flReloadTime;
	float    m_flAttackRate;
	float    m_flMaxPhysicsImpulse;
	
	bool     blsReload;
	bool     blsPrimaryAttack;

	UPROPERTY()
	TArray<AActor*> ArrayActors;
	
	UPROPERTY()
	TArray<FString> hit_physics_material;

	UPROPERTY(EditAnywhere, Category="Pool")
	TArray<USoundBase*> SoundBase;
};


FORCEINLINE Aobject_pool* ABaseWeapon::GetShellPool() const
{
	return pool_object;
}


FORCEINLINE FName ABaseWeapon::GetSocketName() const 
{
	return fSocketName;
}


FORCEINLINE int32 ABaseWeapon::GetMaxAmmo() const 
{
	return imaxAmmo;
}


FORCEINLINE int32 ABaseWeapon::GetCurrentAmmo() const 
{
	return icurrentAmmo;
}


FORCEINLINE int32 ABaseWeapon::GetInvAmmo() const 
{
	return imaxInventoryAmmo;
}

FORCEINLINE int32 ABaseWeapon::GetDamageAmounth() const
{
	return idamage;
}


FORCEINLINE float ABaseWeapon::GetReloadTime() const 
{
	return m_flReloadTime;
}


FORCEINLINE float ABaseWeapon::GetBulletSpread() const 
{
	return m_flBulletSpread;
}


FORCEINLINE float ABaseWeapon::GetMaxShootDistance() const 
{
	return m_flmaxTraceLength;
}


FORCEINLINE float ABaseWeapon::GetAttackRate() const 
{
	return m_flAttackRate;
}


FORCEINLINE float ABaseWeapon::GetMaxPhysicsImpulse() const 
{
	return m_flMaxPhysicsImpulse;
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*here we get a vector for the line trace
 *depending on whether it is a person or a bot*/
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
FORCEINLINE FVector ABaseWeapon::GetShotForwardVector() const 
{
	// Get Controller Player
	const TObjectPtr<AController> Controller = Player->GetController();

	if (Controller != nullptr)
	{
		// check this player controller
		if (Controller->IsA(APlayerController::StaticClass()))
		{
			const TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(Controller);
			if (PlayerController != nullptr && PlayerController->PlayerCameraManager != nullptr)
			{
				// Get Direction Camera Player 
				return  PlayerController->PlayerCameraManager->GetActorForwardVector();
			}
		}
		// check, valid this npc controller 
		else if (Controller->IsA(AAIController::StaticClass()))
		{
			// Get direction npc
			return  Player->GetActorForwardVector();
		}
	}

	// return zero vector if error
	return FVector::ZeroVector;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------*/
/*this function returns the direction of weapon
spread - m_flBulletSpread this is the variable with which we adjust the spread */
/*---------------------------------------------------------------------------------------------------------------------------------------------*/
FORCEINLINE FVector ABaseWeapon::CalculateBulletSpread(const FVector& ShotDirection) const 
{
	float HalfConeAngleRand = FMath::DegreesToRadians(m_flBulletSpread / 2.0f);
	FVector SpreadDirection = FMath::VRandCone(ShotDirection, HalfConeAngleRand);
	
	return SpreadDirection;
}

// Methods for setting values
FORCEINLINE void ABaseWeapon::SetSkeletalMesh(USkeletalMeshComponent* NewMesh)
{
	WeaponSkeletalMeshComponent = NewMesh;
}


FORCEINLINE void ABaseWeapon::SetMaxShootDistance(float fldistance) 
{
	m_flmaxTraceLength = fldistance;
}


FORCEINLINE void ABaseWeapon::SetSocetName(FName newName) 
{
	fSocketName = newName;
}


FORCEINLINE void ABaseWeapon::SetMaxAmmo(int32 iAmmo) 
{
	imaxAmmo = iAmmo;
}


FORCEINLINE void ABaseWeapon::SetCurrentAmmo(int32 iAmmo) 
{
	icurrentAmmo = iAmmo;
}


FORCEINLINE void ABaseWeapon::SetInvAmmo(int32 i_invammo) 
{
	imaxInventoryAmmo = i_invammo;
}



FORCEINLINE void ABaseWeapon::SetDamageAmounth(int32 iamounth)
{
	idamage = iamounth;
}


FORCEINLINE void ABaseWeapon::SetReloadTime(float flnew_time) 
{
	m_flReloadTime = flnew_time;
}


FORCEINLINE void ABaseWeapon::SetAttackRate(float fl_rateattack) 
{
	m_flAttackRate = fl_rateattack;
}


FORCEINLINE void ABaseWeapon::SetBulletSpread(float flspread) 
{
	m_flBulletSpread = flspread;
}


FORCEINLINE void ABaseWeapon::SetPhysicsImpulse(float fl_impulse) 
{
	m_flMaxPhysicsImpulse = fl_impulse;
}


// Sound effects and load
FORCEINLINE void ABaseWeapon::SetFireSound(USoundBase* NewSound)
{
	FireSound = NewSound;
}


FORCEINLINE void ABaseWeapon::SetReloadSound(USoundBase* NewSound)
{
	ReloadSound = NewSound;
}


FORCEINLINE void ABaseWeapon::SetMuzzleFlash(UParticleSystem* NewEffect)
{
	MuzzleFlash = NewEffect;
}


