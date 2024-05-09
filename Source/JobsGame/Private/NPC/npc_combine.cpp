// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC/npc_combine.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogCombineClass);

// Sets default values
Anpc_combine::Anpc_combine()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Default value
	blsIsDead = false;
	m_flGravityScale = 1.0f;
	m_flMassCombine = 80.0f;
	m_flMaxSpeedFly = 1500.0f;
	m_flMaxAcceleration = 1480.0f;
	m_maxFallDead = 500.0f;
	m_flAirControl = 0.5f;
	m_flMaxSpeedWalk = 600.0f;
	m_flMaxSpeedRun = 0.0f;
	m_iMaxHealth = 200.0f;
	m_iCurrentHealth = m_iMaxHealth;
	
	// Load SkeletalMesh
	combine_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	const FSoftObjectPath SkeletalFind(TEXT("/Game/NPC/Combine/Combine"));
	static TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;
	if (SkeletalFind.IsValid())
	{
		SkeletalMesh = Cast<USkeletalMesh>(SkeletalFind.TryLoad());
	}
	if (SkeletalMesh != nullptr)
	{
		combine_mesh->SetSkeletalMesh(SkeletalMesh);
		combine_mesh->SetupAttachment(RootComponent);
		combine_mesh->SetRelativeLocation(FVector(0, 0, -100));
		combine_mesh->SetRelativeRotation(FRotator(0, -90, 0));
	}
	else
	{
		UE_LOG(LogCombineClass, Warning, TEXT("Error Load: %s"), *SkeletalFind.ToString())
	}
	//default settings combine movement   
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	GetCharacterMovement()->MaxAcceleration = GetMaxAcceleration();
	GetCharacterMovement()->GravityScale = GetGravityScale();
	GetCharacterMovement()->AirControl = GetAirControl();
	GetCharacterMovement()->MaxFlySpeed = GetMaxSpeedFly();
	GetCharacterMovement()->MaxWalkSpeed = GetMaxSpeedWalk();
}

// Called when the game starts or when spawned
void Anpc_combine::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->SetMassScale(NAME_Pawn, 60);
	GetCharacterMovement()->Mass = GetMassCharacter();

}

// Called every frame
void Anpc_combine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void Anpc_combine::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
}


// Simulate PhysicsMesh Combine
void Anpc_combine::RagDoll(bool Simulate)
{
	SetRagDollState(Simulate);
	combine_mesh->SetSimulatePhysics(GetRagDoll());
}


