// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "test_props.generated.h"
class UBoxComponent;
class UStaticMesh;

UCLASS()
class Atest_props : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Trigger", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxTrigger;

	UPROPERTY(EditAnywhere, Category="Trigger", meta=(AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> ArrayMeshComponents;
	
public:	
	// Sets default values for this actor's properties
	Atest_props();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void SpawnObject() const;
	
private:
	
	bool is_spawn;
};
