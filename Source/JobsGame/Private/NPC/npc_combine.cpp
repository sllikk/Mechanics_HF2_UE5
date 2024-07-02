// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC/npc_combine.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogCombineClass);

// Sets default values
Anpc_combine::Anpc_combine()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Default value
	m_flDistanceFallDead = 100.0f;
	m_flGravityScale = 1.0f;
	m_flMassCombine = 80.0f;
	m_flMaxSpeedFly = 1500.0f;
	m_flMaxAcceleration = 1100.0f;
	m_maxFallDead = 500.0f;
	m_flAirControl = 0.5f;
	m_flMaxSpeedWalk = 300.0f;
	m_flMaxSpeedRun = 0.0f;
	m_flMaxHealth = 60;
	m_flCurrentHealth = m_flMaxHealth;
	blsIsDead = false;
	
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
		combine_mesh->SetRelativeLocation(FVector(0, 0, -100));
		combine_mesh->SetRelativeRotation(FRotator(0, -90, 0));
		combine_mesh->SetupAttachment(RootComponent);
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

	GetCapsuleComponent()->SetMassOverrideInKg(NAME_All, 75.0f, true);
	GetCharacterMovement()->Mass = GetMassCharacter();
	

	combine_mesh->OnComponentHit.AddDynamic(this, &Anpc_combine::OnHit);
	
}


// Called every frame
void Anpc_combine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!blsIsDead)
	{
		CombineDebug();
	}
	
}


void Anpc_combine::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

}

void Anpc_combine::HandleDamage(int32 damage_amounth, EDamageType DamageType)
{

	if (blsIsDead || GetCurrentHealth() <= 0)
	{
		return;
	}

	switch (DamageType)
	{
	case EDamageType::DMG_BULLET:
		break;
	case EDamageType::DMG_GENERIC:
		break;
//	case EDamageType::DMG_EXPLODE:
		break;

		default:;
	}


	m_flCurrentHealth = FMath::Clamp(m_flCurrentHealth - damage_amounth, 0, m_flMaxHealth);

	if (GetCurrentHealth() <= 0)
	{
		CombineDead();
	}



}


void Anpc_combine::SpawnWeapon(TSubclassOf<AActor> GunClass, FName socketName)
{
	const FTransform orientationSocket = GetCombineMesh()->GetSocketTransform(socketName, RTS_World);
	const TObjectPtr<AActor> newGun = GetWorld()->SpawnActor(GunClass, &orientationSocket);
	if (newGun == nullptr) return;
	newGun->AttachToComponent(GetCombineMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);		
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
													// GamePlay

void Anpc_combine::CombineDebug() const
{
	const FString& strHealth = FString::Printf(TEXT("charger: %d"), GetCurrentHealth());	
	const FColor& Color = FColor::White;

	FVector vecHealthDebug = GetActorLocation();
	vecHealthDebug.Z += 100.0f; 

	DrawDebugString(GetWorld(), vecHealthDebug, strHealth, nullptr, Color, 0.0f, true);

}


void Anpc_combine::RagDoll() const
{
	combine_mesh->SetSimulatePhysics(true);
	UE_LOG(LogCombineClass, Warning, TEXT("Dead: %s"), *this->GetName());
	combine_mesh->TickAnimation(false, true);
	GetCapsuleComponent()->DestroyComponent();
	
}
//------------------------------------------------------------------------------------------------------


void Anpc_combine::Falling()
{
	Super::Falling();

	float MaxFall = GetVelocity().Z;

	if (MaxFall -= 200)
	{
		CombineDead();
	}

}


void Anpc_combine::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	float Impact = NormalImpulse.Size();
	UE_LOG(LogCombineClass, Warning, TEXT("max size: %2.f"), Impact)
	OnHitMesh(Impact);
	combine_mesh->OnComponentHit.RemoveDynamic(this, &Anpc_combine::OnHit);
	
}


void Anpc_combine::OnHitMesh(float Impact)
{
	float MaxImpact = 600;

	if (Impact > MaxImpact)
	{
		SpawnDecals();
	}
}

void Anpc_combine::SpawnDecals()
{
	FVector const& Location = GetCombineMesh()->GetComponentLocation();
	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BloodDecal[0], FVector(0.3, 0.3, 0.3), Location);
	UE_LOG(LogCombineClass, Warning, TEXT("Spawn: "));

}



/*------------------------------------------------------------------------------------------------------------------------------------------------------*/


void Anpc_combine::CombineDead()
{
	blsIsDead = true;

	if (AAIController* Controllers = GetController<AAIController>())
	{
		Controllers->Destroy();  
		RagDoll();

		if(GamePlaySound[0]->IsValidLowLevel()) // Sound Dead
		{
			UGameplayStatics::SpawnSoundAttached(GamePlaySound[0], combine_mesh);
		}
	}
}


