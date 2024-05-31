// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shell.generated.h"
class UStaticMeshComponent;


UCLASS()
class JOBSGAME_API AShell : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="ShellMesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ShellMesh;
	
public:
	// Sets default values for this actor's properties
	AShell();

protected:
	// Called when the game starts or when spawned
	virtual void       BeginPlay() override;
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:

	FORCEINLINE UStaticMeshComponent* GetMeshBullet() const { return ShellMesh; }

private:

	UPROPERTY()
	TObjectPtr<USoundBase> ShellImpactSound;
	
};
