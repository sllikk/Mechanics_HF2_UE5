// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/Debug_Object.h"

DEFINE_LOG_CATEGORY(LogDebug_Object)		
DEFINE_LOG_CATEGORY(LogDebug_ResourceObject)		

ADebug_Object::ADebug_Object()
{
	PrimaryActorTick.bCanEverTick = true;

	PrototypeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	
	FSoftObjectPath FindMesh(TEXT("/Game/LevelPrototyping/Meshes/Prototype"));	
	UStaticMesh* StaticMesh = nullptr;

	if (FindMesh.IsValid())
	{
		StaticMesh = Cast<UStaticMesh>(FindMesh.TryLoad());
	}
	if (StaticMesh != nullptr)
	{
		PrototypeMeshComponent->SetStaticMesh(StaticMesh);
	}
	else
	{
		UE_LOG(LogDebug_ResourceObject, Warning, TEXT("Eror find %s"), *FindMesh.ToString())
	}
	
}


void ADebug_Object::DebugPrototype()
{
	// ДОДЕЛАТЬ ВЕС И РОТАЦИЮ И ЛОКАЦИЮ
	FString Weight = FString::Printf(TEXT("Mass: %f"), PrototypeMeshComponent->GetMass());

	FVector Location = PrototypeMeshComponent->GetComponentLocation();
	float XVec = Location.X;
	float YVec = Location.Y;
	float ZVec = Location.Z;

	FRotator Rotation = PrototypeMeshComponent->GetComponentRotation();
	float Pitch = Rotation.Pitch; 
	float Yaw = Rotation.Yaw;
	float Roll = Rotation.Roll;
	
	FString StringLocation = FString::Printf(TEXT("Loc: X = %f, Y = %f, Z = %f" ), XVec, YVec, ZVec);
	FString StringRotation = FString::Printf(TEXT("Rot: Pitch = %f, Yaw = %f, Roll = %f"), Pitch, Yaw, Roll);
	FVector TextLocation = PrototypeMeshComponent->GetComponentLocation() + FVector(0,0,10.0f);
	FVector TextRotation = Rotation.RotateVector(FVector(0,0,20.0f));
	FColor TextColor = FColor::White;
	
	DrawDebugString(GetWorld(), TextLocation, Weight, this, TextColor, 0, false);
	DrawDebugString(GetWorld(), TextRotation, Weight, this, TextColor, 0, false);
	
	
	DrawDebugString(GetWorld(), TextLocation + FVector(0, 0, -20), StringLocation, this, TextColor, false);
	DrawDebugString(GetWorld(), TextRotation + FVector(0, 0, -10), StringRotation, this, TextColor, false);

}

void ADebug_Object::GetWeight()
{
}


void ADebug_Object::BeginPlay()
{
	Super::BeginPlay();
	
	PrototypeMeshComponent->SetSimulatePhysics(true);
	PrototypeMeshComponent->SetMassOverrideInKg(NAME_None, 70, true);
	


}


void ADebug_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DebugPrototype();

}




