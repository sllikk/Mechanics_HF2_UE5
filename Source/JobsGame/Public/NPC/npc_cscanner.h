// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "npc_cscanner.generated.h"
class USkeletalMeshComponent;
class UBehaviorTree;
class UFloatingPawnMovement;

UCLASS()
class JOBSGAME_API Anpc_cscanner : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> CScanner_Mesh;

	UPROPERTY(EditAnywhere, Category="SkeletalMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;	
	
public:
	// Sets default values for this pawn's properties
	Anpc_cscanner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, Category="AI")
	UBehaviorTree* TreeAsset;
	
};
