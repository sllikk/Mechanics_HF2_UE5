// Fill out your copyright notice in the Description page of Project Settings.


#include "Shell.h"

#include "NPC_WEAPON/BaseWeapon.h"


// Sets default values
AShell::AShell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = ShellMesh;	
	
	const FSoftObjectPath FindMesh(TEXT("/Game/Weapon/Shellmesh/smg_bullet"));
	static TObjectPtr<UStaticMesh> LoadMesh = nullptr;

	if (FindMesh.IsValid())
	{
		LoadMesh = Cast<UStaticMesh>(FindMesh.TryLoad());
	}
	if (LoadMesh != nullptr)
	{
		ShellMesh->SetStaticMesh(LoadMesh);
	}
	
	ShellMesh->SetWorldScale3D(FVector(0.1, 0.1, 0.1));

}

// Called when the game starts or when spawned
void AShell::BeginPlay()
{
	Super::BeginPlay();

	ShellMesh->SetSimulatePhysics(true);

	ShellMesh->OnComponentHit.AddDynamic(this, &AShell::OnComponentHit);
}

void AShell::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp != nullptr)
	{
		UE_LOG(LogWeapon, Warning, TEXT("Hit"));
	}
	
}





