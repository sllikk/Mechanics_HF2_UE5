// Fill out your copyright notice in the Description page of Project Settings.

#include "World_InteractObject/hopper_mine.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystem.h"

#define HOPPER_MINE_MAX_FLIPS 5


Ahopper_mine::Ahopper_mine()
{
	PrimaryActorTick.bCanEverTick = true;

	// Default SubObject
	Mine_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	Detected_Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	Detected_Light->SourceRadius = 10.0f;
	// Load Mesh
	static const FSoftObjectPath FinderMesh(TEXT("/Game/World_InteractObject/HopperMine/Combine_mine"));
	USkeletalMesh* SkeletalMesh = nullptr;
	if (FinderMesh.IsValid())
	{
		SkeletalMesh = Cast<USkeletalMesh>(FinderMesh.TryLoad());
	}
	if (SkeletalMesh != nullptr)
	{
		Mine_SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
	}
	
	// Load Partecles 
	static const FSoftObjectPath FinderParticle(TEXT("/Game/VFX/Particles/Explosion/Hopper_Explosion"));
	UParticleSystem* FoundParticle = nullptr;
	if(FinderParticle.IsValid())
	{
		FoundParticle = Cast<UParticleSystem>(FinderParticle.TryLoad());
	}
	if (FoundParticle != nullptr)
	{
		ExplodeParticle = FoundParticle;
	}

	SetRootComponent(Mine_SkeletalMesh);
	Mine_SkeletalMesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));

	FVector const& SocketLocation = Mine_SkeletalMesh->GetSocketLocation(LightSocket);
	FRotator const& SocketRotation = Mine_SkeletalMesh->GetSocketRotation(LightSocket);
	Detected_Light->SetupAttachment(Mine_SkeletalMesh, LightSocket);

}

void Ahopper_mine::BeginPlay()
{
	Super::BeginPlay();

	
}

void Ahopper_mine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*-------------------------------------------------------------------------------------------------------------*/
							// Func Mine_State
/*-------------------------------------------------------------------------------------------------------------*/

void Ahopper_mine::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}
/*-------------------------------------------------------------------------------------------------------------*/

void Ahopper_mine::Flip(const FVector& vecForce, const FVector& AngularImpulce)
{
}
/*-------------------------------------------------------------------------------------------------------------*/

void Ahopper_mine::SetMineState(int iState)
{
	m_iMineState = iState;
}
/*-------------------------------------------------------------------------------------------------------------*/

void Ahopper_mine::SearchThink()
{

}
/*-------------------------------------------------------------------------------------------------------------*/

void Ahopper_mine::BounceThink()
{

}
/*-------------------------------------------------------------------------------------------------------------*/

void Ahopper_mine::SettleThink()
{

}
/*-------------------------------------------------------------------------------------------------------------*/

void Ahopper_mine::CaptiveThink()
{

}
/*-------------------------------------------------------------------------------------------------------------*/

void Ahopper_mine::ExplodeThink()
{

}
/*-------------------------------------------------------------------------------------------------------------*/

void Ahopper_mine::ExplodeTouch(AActor* pOther)
{

}
/*-------------------------------------------------------------------------------------------------------------*/

void Ahopper_mine::Wake(bool bWake)
{

}


