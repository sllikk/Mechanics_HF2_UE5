// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Player/MyCharacter.h"
#include "grab_sphere.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPicUp, AMyCharacter* , Character);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOBSGAME_API Ugrab_sphere : public USphereComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	Ugrab_sphere();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:

	UPROPERTY(EditAnywhere, Category="OnPickUp", BlueprintAssignable)
	FPicUp PicUp;

};
