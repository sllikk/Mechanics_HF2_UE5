// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Shared/damage.h"
#include "npc_combine.generated.h"
class USkeletalMeshComponent;
class UBehaviorTree;
class UDecalComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogCombineClass, Log, All);

UCLASS()
class JOBSGAME_API Anpc_combine : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> combine_mesh;

	UPROPERTY(EditAnywhere, Blueprintable, Category="Decals", meta=(AllowPrivateAccess = "true"))
	TArray<UMaterialInstance*> BloodDecal;
	
public:
	// Sets default values for this character's properties
	Anpc_combine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called Hit Land
	virtual void Landed(const FHitResult& Hit) override;

public:
	// Behavior Tree this npc
	UPROPERTY(Transient, EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> TreeAsset;
	
	UFUNCTION(BlueprintCallable, Category="AttachGun")
	void SpawnWeapon(TSubclassOf<AActor> GunClass, FName socketName);

	UFUNCTION(BlueprintCallable, Category="AttachGun")
	void Damage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
				AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	// GamePlay Sound this npc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="gameplay_sound")
	TArray<USoundBase*> GamePlaySound;


	
#pragma region Getters_Setters 
	UFUNCTION(Blueprintable, Category="Mesh")
	FORCEINLINE	USkeletalMeshComponent*		GetCombineMesh() const							 { return combine_mesh; }  
	UFUNCTION(BlueprintCallable, Category="Dead")
	FORCEINLINE bool						ISDead() const									 { return  blsIsDead; }
	FORCEINLINE float						GetMaxSpeedWalk() const							 { return m_flMaxSpeedWalk; }
	FORCEINLINE void						SetMaxSpeedWalk(float flMaxSpeedWalk)			 { m_flMaxSpeedWalk = flMaxSpeedWalk; }
	FORCEINLINE	float						GetMaxAcceleration() const						 { return m_flMaxAcceleration; }
	FORCEINLINE	void						SetMaxAcceleration(float fl_MaxAcceleration)	 { m_flMaxAcceleration =  fl_MaxAcceleration; } 
	FORCEINLINE	float						GetGravityScale() const							 { return m_flGravityScale; }
	FORCEINLINE	void						SetGravityScale(float fl_GravityScale)		 	 { m_flGravityScale = fl_GravityScale; }
	FORCEINLINE	float						GetAirControl() const							 { return m_flAirControl; }
	FORCEINLINE	void						SetAirControl(float fl_AirControl)				 { m_flAirControl = fl_AirControl; }
	FORCEINLINE	float						GetMaxSpeedFly() const							 { return m_flMaxSpeedFly; }
	FORCEINLINE	void						SetMaxSpeedFly(float fl_MaxSpeedFly)			 { m_flMaxSpeedFly = fl_MaxSpeedFly; }
	FORCEINLINE	float						GetMassCharacter() const						 { return m_flMassCombine; }
	FORCEINLINE	void						SetMassCharacter(float fl_MassCharacter)	 	 { m_flMassCombine = fl_MassCharacter; }
	FORCEINLINE float						GetCurrentHealth() const						 { return m_flCurrentHealth; }				
	FORCEINLINE float						GetMaxHealth() const							 { return m_flMaxHealth; }				
	FORCEINLINE	void						SetMaxHealth(float iMaxHealth) 					 { m_flMaxHealth = iMaxHealth; }					
	
	#pragma endregion			

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

	void	CombineDead();
	void	CombineDebug() const;
	void	RagDoll() const;
	void	Falling() override;
	void	OnHitMesh(float Impact);
	void    SpawnDecals();
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dead")	
	bool		blsIsDead;
	float		m_flMaxSpeedWalk;
	float		m_flMaxSpeedRun;
	float		m_flMaxAcceleration;        
	float		m_flGravityScale;
	float		m_flAirControl;
	float		m_flMaxSpeedFly;
	float		m_flMassCombine;
	float		m_maxFallDead;
	float		m_flMaxHealth;
	float		m_flCurrentHealth;
	float		m_flDistanceFallDead;
	

};
