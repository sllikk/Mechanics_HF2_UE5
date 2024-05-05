// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/npc_cscanner.h"

#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
Anpc_cscanner::Anpc_cscanner()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CScanner_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	const FSoftObjectPath FindMesh(TEXT("/Game/NPC/City_Scanner/City_Scanner"));
	USkeletalMesh* SkeletalMesh = nullptr;
	if (FindMesh.IsValid())
	{
		SkeletalMesh = Cast<USkeletalMesh>(FindMesh.TryLoad());
	}
	if (SkeletalMesh != nullptr)
	{
		CScanner_Mesh->SetSkeletalMesh(SkeletalMesh);
	}
	else
	{
		UE_LOG(LogLoad, Warning, TEXT("Error find: %s"), *FindMesh.ToString());
	}


}

// Called when the game starts or when spawned
void Anpc_cscanner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Anpc_cscanner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


