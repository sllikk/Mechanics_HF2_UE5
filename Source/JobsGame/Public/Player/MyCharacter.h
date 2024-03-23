// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"
class UInputAction;
class UInputMappingContext;
class USkeletalMeshComponent;
class UCameraComponent;
class USoundBase;
struct FInputActionValue;


DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Log, All);


UCLASS(Config = Game)

class JOBSGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

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

	#pragma endregion


public:
	
	AMyCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<UCameraComponent> FirstPersonCamera;

private:

	virtual ~AMyCharacter() override;
	
public:	
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCamera; }

protected:

#pragma region FUNC_INPUT

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Run();
	void StopRun();

	void StartCrouch();
	void StopCrouch();

	void Interact();

#pragma endregion

protected:

	//UPROPERTY(VisibleAnywhere, Category = "DoorActor")
	//TObjectPtr<AWoodDoor> WoodDoor;




private:

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
	float m_MassCharacter = 85.0f;
	UPROPERTY(Config)
	float m_JumpHeight = 300.0f;
	UPROPERTY(Config)
	float m_LineTraceLength = 180;

private:

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> SprintSound;


private:

	void AddIgnoredActorToLineTrace(const FName& GroupName, FCollisionQueryParams& QueryParams);



};
