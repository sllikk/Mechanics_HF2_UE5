// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "debug_entity.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FDebugInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	TObjectPtr<AActor> Entity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	TObjectPtr<UStaticMeshComponent> debug_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	float flmassEntity;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	float flstressEntity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	int32 ihealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	FString EnumAsString;
};



UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOBSGAME_API Udebug_entity : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	Udebug_entity();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category="Debug")
	void UpdateDebug() const;
	 
	UFUNCTION(BlueprintCallable)
	void SetDebugEntity(AActor* DebugActor);

	UFUNCTION(BlueprintCallable)
	void SetDebugMesh(UStaticMeshComponent* DebugMesh);
	
	UFUNCTION(Blueprintable, BlueprintSetter)
	FORCEINLINE void SetDebugHealth(int32 idebug) { DebugInfo.ihealth = idebug; }
	
	UFUNCTION(Blueprintable, BlueprintSetter)
	FORCEINLINE void SetDebugStress(float fldebug) { DebugInfo.flstressEntity = fldebug; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDebugEnumAsString(const FString& strEnum) { DebugInfo.EnumAsString = strEnum; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
	FDebugInfo DebugInfo;

	UFUNCTION(BlueprintCallable)
	FString GetEnumValueAsString(const FString& EnumName, int32 EnumValue); 
	
private:

	
};



FORCEINLINE void Udebug_entity::SetDebugEntity(AActor* DebugActor)
{
	DebugInfo.Entity = DebugActor;
}

FORCEINLINE void Udebug_entity::SetDebugMesh(UStaticMeshComponent* DebugMesh)
{
	DebugInfo.debug_mesh = DebugMesh;
}
