// Fill out your copyright notice in the Description page of Project Settings.

#include "World_InteractObject/HopperMine.h"
#include "Components/PointLightComponent.h"
#include "Player/MyCharacter.h"
#include "Components/SphereComponent.h"
#include "WorldActors/Door.h"

DEFINE_LOG_CATEGORY(LogLoadResourceMine);
DEFINE_LOG_CATEGORY(LogHopper);

AHopperMine::AHopperMine()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	// Loading and Settings mine and Mine Component 
	HopperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HopperMesh")); 
	DetectedSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectedSphere"));
	//ActiveSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ActivationSphere"));
	LightDetector = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightDetector"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HopperMesh(TEXT("/Game/World_InteractObject/HopperMine/Hoppers"));
	if (HopperMesh.Succeeded())
	{
		HopperMeshComponent->SetStaticMesh(HopperMesh.Object);
	}
	else
	{
		UE_LOG(LogLoadResourceMine, Warning, TEXT("Eror find object mesh"));
	}

	
	SetRootComponent(HopperMeshComponent);
	HopperMeshComponent->SetWorldScale3D(FVector(32.0f,32.0f,35.0f));

	// Settings component mine
	// Light component
	LightDetector->SetupAttachment(HopperMeshComponent);
	LightDetector->SetWorldLocation(FVector(0.0f, 0.0f, 0.32));
	LightDetector->Intensity = 10000.0f;	
	LightDetector->AttenuationRadius = 30.0f;
	LightDetector->IntensityUnits = ELightUnits::Lumens;	
	LightDetector->bAffectsWorld = true;	

	// Sphere Component	
	DetectedSphere->SetupAttachment(HopperMeshComponent);
	DetectedSphere->InitSphereRadius(45.0f);

}


void AHopperMine::BeginPlay()
{
	Super::BeginPlay();

	TArray<USoundBase*> MineSound;
	TArray<FLoadSoundResource> ResourcesToLoad = {
	{"/Game/Sound/Sound_InteractObj/Cue/Mine_active_loop_Cue", nullptr},
	{"/Game/Sound/Sound_InteractObj/Cue/Mine_deactivate_Cue", nullptr},
	{"/Game/Sound/Sound_InteractObj/Cue/Mine_deploy_Cue", nullptr},
	
	};
	ResourcesToLoad.Reserve(3);	
	
	for (FLoadSoundResource& Resource : ResourcesToLoad)
	{
		Resource.LoadedResource = LoadObject<UObject>(nullptr,*Resource.ResourcePath);
		if (!Resource.LoadedResource)
		{
			UE_LOG(LOG_LOADING_RESOURCE, Warning, TEXT("Eror find sound object"));
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

	// Physics Mine
	HopperMeshComponent->SetSimulatePhysics(true);
	HopperMeshComponent->SetMassOverrideInKg(NAME_None, 90, true);

	DetectedSphere->OnComponentBeginOverlap.AddDynamic(this, &AHopperMine::OnDetectionRadiusBeginOverlap);
	DetectedSphere->OnComponentBeginOverlap.AddDynamic(this, &AHopperMine::OnDetectionRadiusEndOverlap);
	
}


void AHopperMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AHopperMine::OnDetectionRadiusBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(StatMine == EStatMine::ACTIVATE)
	{
		if (OtherActor != nullptr)
		{
			MyCharacter = Cast<AMyCharacter>(OtherActor);
			if (MyCharacter)
			{
				UE_LOG(LogHopper, Warning, TEXT("Detected MyCharacter"));
				
				
				


				
			}
		}
	}	
}

void AHopperMine::OnDetectionRadiusEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}


void AHopperMine::ActivateMine()
{

}




