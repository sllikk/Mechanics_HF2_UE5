// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/Door.h"

DEFINE_LOG_CATEGORY(LOG_LOADING_RESOURCE);
DEFINE_LOG_CATEGORY(LogDoor);

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Loading resource and set StaticMesh
	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorComponent"));
	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameComponent"));
	
	TArray<FInfoLoadResourse> ResourseToLoad = {

		{"/Game/WorldActors/Door/sDoor", nullptr},
		{"/Game/WorldActors/Door/sDoorFrame", nullptr},
		{"/Game/WorldActors/Door/DoorCurveFloat", nullptr},
	};	
	
	for (FInfoLoadResourse& Resourse : ResourseToLoad)
	{
		Resourse.LoadingResource = LoadObject<UObject>(nullptr, *Resourse.ResourceLoadPath);
		if (!Resourse.LoadingResource)
		{
			UE_LOG(LOG_LOADING_RESOURCE, Warning, TEXT("Eror find object !!!!!!!!!"))
		}
	}	
	for (const FInfoLoadResourse Resourse : ResourseToLoad)
	{
		UStaticMesh* DoorMesh = Cast<UStaticMesh>(ResourseToLoad[0].LoadingResource);
		UStaticMesh* DoorFrameMesh = Cast<UStaticMesh>(ResourseToLoad[1].LoadingResource);

		if (DoorMesh)
		{
			DoorComponent->SetStaticMesh(DoorMesh);
		}
		if (DoorFrameMesh)
		{
			DoorFrameComponent->SetStaticMesh(DoorFrameMesh);
		}
	}
	
	SetRootComponent(DoorComponent);
	DoorFrameComponent->SetupAttachment(DoorComponent);

}


void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<FInfoLoadResourse> SoundResourceToLoad = {
		
		{"/Game/Sound/ActorSound/Cue/Door_move_Cue", nullptr},
		{"/Game/Sound/ActorSound/Cue/Door_stop_Cue", nullptr},
	};

	for (FInfoLoadResourse& Resourse : SoundResourceToLoad)
	{
		Resourse.LoadingResource = LoadObject<UObject>(nullptr, *Resourse.ResourceLoadPath);
		if (!Resourse.LoadingResource)
		{
			UE_LOG(LOG_LOADING_RESOURCE, Warning, TEXT("Eror find sound object !!!!!!!!!"));
		}
	}
	for (const FInfoLoadResourse& Resourse : SoundResourceToLoad)
	{
		USoundBase* Door_Move = Cast<USoundBase>(SoundResourceToLoad[0].LoadingResource);
		USoundBase* Door_Close = Cast<USoundBase>(SoundResourceToLoad[1].LoadingResource);

		if (Door_Move)
		{
			OpenDoorSound = Door_Move;
		}
		if (Door_Close)
		{
			CloseDoorSound = Door_Close;
		}

	}

}	


void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ADoor::Interact()
{
}

void ADoor::OpenDoor(float Value)
{
}

void ADoor::DoorOnsameSide()
{
}

