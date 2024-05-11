// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_WEAPON/shotgun.h"


// Sets default values
Ashotgun::Ashotgun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShotgunSkeletal = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
//	Shells = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// Load Skeletal mesh shotgun
	const FSoftObjectPath GunPath(TEXT("/Game/Weapon/ShotGun/Spas12")); 	
	static TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;
	if (GunPath.IsValid())
	{
		SkeletalMesh = Cast<USkeletalMesh>(GunPath.TryLoad());
	}
	if (SkeletalMesh != nullptr)
	{
		ShotgunSkeletal->SetSkeletalMesh(SkeletalMesh);

	} 
	else
	{
		UE_LOG(LogLoad, Warning, TEXT("Error Load: %s"), *GunPath.ToString())
	}
	// Load Static mesh shell for shotgun
/*
	const FSoftObjectPath ShellPath(TEXT("/Game/Weapon/ShotGun/Shell/shell_shotgun"));
	static TObjectPtr<UStaticMesh> ShellMesh = nullptr;
	if (ShellPath.IsValid())
	{
		ShellMesh = Cast<UStaticMesh>(ShellPath.TryLoad());
	}
	if (ShellMesh != nullptr)
	{
		Shells->SetStaticMesh(ShellMesh);		
	}
*/
}

// Called when the game starts or when spawned
void Ashotgun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Ashotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

void Ashotgun::Fire()
{

}



