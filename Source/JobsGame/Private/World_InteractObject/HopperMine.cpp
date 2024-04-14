// Fill out your copyright notice in the Description page of Project Settings.

#include "World_InteractObject/HopperMine.h"
#include "Components/AudioComponent.h"
#include "Components/PointLightComponent.h"
#include "Player/MyCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "WorldActors/Door.h"

// LOG TEST

DEFINE_LOG_CATEGORY(LogLoadResourceMine);
DEFINE_LOG_CATEGORY(LogHopper);

AHopperMine::AHopperMine()
{
	PrimaryActorTick.bCanEverTick = true;

	// Loading and Settings mine and Mine Component 
	HopperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HopperMesh")); 
	DetectedCollision = CreateDefaultSubobject<USphereComponent>(TEXT("DetectedSphere"));
	ActivateCollision = CreateDefaultSubobject<USphereComponent>(TEXT("DetectedBox"));
	LightDetector = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightDetector"));
	
	const FSoftObjectPath HopperMesh(TEXT("/Game/World_InteractObject/HopperMine/Hoppers"));
	UStaticMesh* StaticMesh = nullptr;

	if (HopperMesh.IsValid())
	{
		StaticMesh = Cast<UStaticMesh>(HopperMesh.TryLoad());
	}
	if (StaticMesh != nullptr)
	{
		HopperMeshComponent->SetStaticMesh(StaticMesh);
	}
		
	else
	{
		UE_LOG(LogLoadResourceMine, Warning, TEXT("Error find: %s"),*HopperMesh.ToString());
	}

	const FSoftObjectPath FinderParticle(TEXT("/Game/VFX/Particles/Explosion/Hopper_Explosion"));
	UParticleSystem* FoundParticle = nullptr;

	if(FinderParticle.IsValid())
	{
		FoundParticle = Cast<UParticleSystem>(FinderParticle.TryLoad());
	}
		if (FoundParticle != nullptr)
		{
			ExplosionEffects = FoundParticle;
		}
	else
	{
		UE_LOG(LogLoadResourceMine, Warning, TEXT("Error find: %s"), *FinderParticle.ToString());
	}

	// Root Component mesh
	SetRootComponent(HopperMeshComponent);
	HopperMeshComponent->SetWorldScale3D(FVector(42.0f,42.0f,42.50f));

	// Settings component mine
	// Light component
	LightDetector->SetupAttachment(HopperMeshComponent);
	LightDetector->SetWorldLocation(FVector(0.0f, 0.0f, 0.32));
	LightDetector->AttenuationRadius = 30.0f;
	LightDetector->SetVisibility(false);
	LightDetector->IntensityUnits = ELightUnits::Lumens;	
	LightDetector->bAffectsWorld = true;	

	ActivateCollision->SetupAttachment(HopperMeshComponent);
	ActivateCollision->InitSphereRadius(6.2f);
	DetectedCollision->SetupAttachment(HopperMeshComponent);
	DetectedCollision->InitSphereRadius(13.0f);
}


void AHopperMine::BeginPlay()
{
	Super::BeginPlay();

	// Load sound source file
	TArray<FLoadSoundResource> ResourcesToLoad = {

	FLoadSoundResource{TEXT("/Game/Sound/Sound_InteractObj/Cue/Mine_active_loop_Cue"), nullptr},
	FLoadSoundResource{TEXT("/Game/Sound/Sound_InteractObj/Cue/Mine_deactivate_Cue"), nullptr},
	FLoadSoundResource{TEXT("/Game/Sound/Sound_InteractObj/Cue/Mine_deploy_Cue"), nullptr},
	FLoadSoundResource{TEXT("/Game/Sound/Sound_InteractObj/Cue/mine_blip_Cue"), nullptr},
	FLoadSoundResource{TEXT("/Game/Sound/Sound_InteractObj/Cue/explode5_Cue"), nullptr},
	
	};

	for (FLoadSoundResource& Resource : ResourcesToLoad)
	{
		Resource.LoadedResource = LoadObject<UObject>(nullptr,*Resource.ResourcePath);
		if (Resource.LoadedResource)
		{
			UE_LOG(LOG_LOADING_RESOURCE, Warning, TEXT("Loaded: %s"), *Resource.ResourcePath);
		}
		else
		{
			UE_LOG(LOG_LOADING_RESOURCE, Warning, TEXT("Error Loaded: %s"), *Resource.ResourcePath)
		}
	}
	for (const FLoadSoundResource& Resource : ResourcesToLoad)
	{
		USoundBase* ArrayLoadedSound = Cast<USoundBase>(Resource.LoadedResource);

		if (ArrayLoadedSound)
		{
			MineSound.Add(ArrayLoadedSound);
		}		
		
	}

	//Collision Detected
	DetectedCollision->OnComponentBeginOverlap.AddDynamic(this, &AHopperMine::OnDetectionRadiusBeginOverlap);
	DetectedCollision->OnComponentEndOverlap.AddDynamic(this, &AHopperMine::OnDetectionRadiusEndOverlap);
	// Collision Activate
	ActivateCollision->OnComponentBeginOverlap.AddDynamic(this, &AHopperMine::BeginActivateMine);	

	//Initialisation Array AudioComponent
	for (int16 i = 0; i < MineSound.Num(); ++i)
	{
		FString SoundName = FString::Printf(TEXT("ExplosionSound: %hd"), i);
		TObjectPtr<UAudioComponent> AttachAudioComponent = UGameplayStatics::SpawnSoundAttached(MineSound[i], HopperMeshComponent);
		AudioComponent.Add(AttachAudioComponent);
		AudioComponent[i]->Stop();
	}
	
}


void AHopperMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


// Detection Actors and Player
void AHopperMine::OnDetectionRadiusBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MyCharacter = Cast<AMyCharacter>(OtherActor);

	if (blsActivate)
	{
		return;
	}
	
	if (MineSound.IsValidIndex(0) && AudioComponent[0] != nullptr)
	{
		UE_LOG(LogHopper, Warning, TEXT("Detected "));
		AudioComponent[0]->Play();

		if (LightDetector != nullptr)
		{
			LightDetector->SetVisibility(true);
			LightDetector->SetLightColor(FLinearColor(1.0f, 0.0f,0.0f));
		}
	}

}


void AHopperMine::OnDetectionRadiusEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (MyCharacter && OtherActor == MyCharacter)
	{
		if (blsActivate)
		{
			return;
		}
		
		if (MineSound.IsValidIndex(1) && AudioComponent[1] != nullptr)
		{
			UE_LOG(LogHopper, Warning, TEXT("OnDetected"));
			AudioComponent[0]->Stop();
			AudioComponent[1]->Play();
			LightDetector->SetVisibility(false);
		}
			
	}
	
}


// Activate Mine
void AHopperMine::BeginActivateMine(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MyCharacter = Cast<AMyCharacter>(OtherActor);

	if (blsActivate)
	{
		return;
	}
	
	if (MyCharacter && OtherActor == MyCharacter)
	{
		if (MineSound.IsValidIndex(2) && AudioComponent[2] != nullptr)
		{
			AudioComponent[0]->Stop();
			AudioComponent[1]->Stop();
			UE_LOG(LogHopper, Warning, TEXT("MINE ACTIVATE"));
			ActivateMine();
		}
	}
}


void AHopperMine::ActivateMine()
{
	if (HopperMeshComponent)
	{
		blsActivate = true;
 
		HopperMeshComponent->SetSimulatePhysics(true);
		HopperMeshComponent->SetMassOverrideInKg(NAME_None, 120, true);
		const float ImpulseStrengh = 900.0f;

		HopperMeshComponent->AddImpulse(FVector(0,0, 1) * ImpulseStrengh, NAME_None, true);
		AudioComponent[3]->Play();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AHopperMine::Explode, 1.45f, false);

	}
	
}


void AHopperMine::Explode()
{
	if (MineSound.IsValidIndex(3) && MineSound.IsValidIndex(4))
	{
		if (AudioComponent[4] != nullptr)
		{
			AudioComponent[4]->Play();
			/*
						UCustomDamageType* CustomDamage = NewObject<UCustomDamageType>();
						if (CustomDamage)
						{
							CustomDamage->DamageType = ECustomDamageType::DMG_EXPLOSION;
							FDamageTypeData DataDamage = CustomDamage->GetDamageTypeData();
							m_RadiusDamage *= DataDamage.DamageMultiplayer; 
							TArray<AActor*> IgnoreActors;
							UGameplayStatics::ApplyRadialDamage(this, m_RadiusDamage, GetActorLocation(), m_RadiusExplosion, CustomDamage->GetClass(), IgnoreActors, this, GetInstigatorController());
							UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffects, GetActorLocation());
			
						}
			
			
						Destroy();
						
			*/		}
	}
}


