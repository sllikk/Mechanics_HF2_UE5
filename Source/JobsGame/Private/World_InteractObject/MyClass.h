// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "MyClass.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, class AMyCharacter*, Character);

UCLASS(BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOBSGAME_API UMyClass : public USphereComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPickUp PickUp;
	
	UMyClass();

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};