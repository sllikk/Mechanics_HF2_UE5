// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "GameFramework/Actor.h"
#include "Player/MyCharacter.h"
#include "BaseWeapon.generated.h"
class USkeletalMeshComponent;
class USoundBase;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogWeapon, All, Log);

UCLASS()
class JOBSGAME_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> WeaponMappingContext;

	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere, Category="Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ReloadAction;
	
	UPROPERTY(EditAnywhere, Category="AmmoShell", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Shell;
	
public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void		AttachWeapon(AMyCharacter* Character);
	

public:
	

	FORCEINLINE	USkeletalMeshComponent*  GetSkeletalMeshComponent() const					{ return WeaponSkeletalMeshComponent; }	
	FORCEINLINE	void					 SetSkeletalMesh(USkeletalMeshComponent* NewMesh)	{ WeaponSkeletalMeshComponent = NewMesh;}  
	FORCEINLINE	float					 GetMaxShootDistance() const						{ return  m_flmaxTraceLength; }
	FORCEINLINE void					 SetMaxShootDistance(float fldistance)				{ m_flmaxTraceLength = fldistance; }
	FORCEINLINE FName					 GetSocketName() const								{ return SocketName; }
	FORCEINLINE void					 SetSocetName(FName newName)						{ SocketName = newName; }
	FORCEINLINE FVector					 GetShotForwardVector() const;														// Shot Direction Player or npc
	FORCEINLINE int32					 GetMaxAmmo() const									{ return imaxAmmo; }
	FORCEINLINE void					 SetMaxAmmo(int32 iAmmo) 							{ imaxAmmo = iAmmo; }
	FORCEINLINE int32					 GetCurrentAmmo() const								{ return icurrentAmmo; }
	FORCEINLINE int32					 GetInvAmmo() const									{ return  imaxInventoryAmmo; }	
	FORCEINLINE void					 SetInvAmmo(int32 i_invammo)						{ imaxInventoryAmmo = i_invammo; }	
	FORCEINLINE float					 GetReloadTime() const								{ return m_flReloadTime; }
	FORCEINLINE void					 SetReloadTime(float flnew_time)					{ m_flReloadTime =  flnew_time; }				 
    	
	FORCEINLINE void					 LoadSkeletalMesh(const FString& Path)  const; // Load Weapon Mesh
	
	virtual void Fire();	
	virtual void Reload();
	virtual void FinishReload();
	virtual void Debug() const;

	void ConsumeAmmo(int32 iAmmo);
	
private:

	UPROPERTY()
	TObjectPtr<AMyCharacter> Player;
	UPROPERTY()
	TObjectPtr<AActor> WeaponOwner;

	FTimerHandle ReloadTimer;
	
	int32	 imaxAmmo;
	int32	 icurrentAmmo;
	int32	 imaxInventoryAmmo;
	float	 m_flmaxTraceLength;
	FName	 SocketName;			// Socket for shoot 
	float    m_flReloadTime;

	bool    blsReload;
	

};
