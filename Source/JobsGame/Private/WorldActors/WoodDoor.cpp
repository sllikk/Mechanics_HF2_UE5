// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/WoodDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY(LogLoandingResource);
DEFINE_LOG_CATEGORY(LogWoodDoor);


struct FLoadResource
{
	FString ResourcePath;
	UObject* LoadedResource;
};



AWoodDoor::AWoodDoor()
{

	PrimaryActorTick.bCanEverTick = true;

	DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));

	//Array load resource
	TArray<FLoadResource> ResourceToLoad = {

	{"/Game/WorldActors/Door/sDoor", nullptr },
	{"/Game/WorldActors/Door/sDoorFrame", nullptr },
	{"/Game/WorldActors/Door/DoorCurveFloat", nullptr },

	};

	for (FLoadResource& Resource : ResourceToLoad) {

		Resource.LoadedResource = LoadObject<UObject>(nullptr, *Resource.ResourcePath);

		if (!Resource.LoadedResource)
		{
			UE_LOG(LogLoandingResource, Warning, TEXT("Eror find object!!!!!!!!!"))
		}
	}

	//Only loaded Meshes and curve float 	
	for (const FLoadResource& Resource : ResourceToLoad)
	{
		if (Resource.LoadedResource)
		{
			UStaticMesh* DoorMesh = Cast<UStaticMesh>(ResourceToLoad[0].LoadedResource);
			UStaticMesh* DoorFrameMesh = Cast<UStaticMesh>(ResourceToLoad[1].LoadedResource);
			UCurveFloat* LoadCurveFloat = Cast<UCurveFloat>(ResourceToLoad[2].LoadedResource);

			if (DoorMesh)
			{
				DoorComponent->SetStaticMesh(DoorMesh);
			}
			if (DoorFrameMesh)
			{
				DoorFrameComponent->SetStaticMesh(DoorFrameMesh);
			}
			if (LoadCurveFloat)
			{
				CurveFloat = LoadCurveFloat;
			}	
		}
	}


}


void AWoodDoor::BeginPlay()
{
	Super::BeginPlay();
	
	
	// Load Sound door
	TArray<FLoadResource> ResourceSound = {

	{"/Game/Sound/ActorSound/Cue/Door_move_Cue", nullptr },
	{"/Game/Sound/ActorSound/Cue/Door_stop_Cue", nullptr },
	
	};

	for (FLoadResource& Resource : ResourceSound)
	{
		Resource.LoadedResource = LoadObject<UObject>(nullptr, *Resource.ResourcePath);
		
		if (!Resource.LoadedResource)
		{
			UE_LOG(LogLoandingResource, Warning, TEXT("Eror find sound object!!!!!!!"));
		}
	}

	for (const FLoadResource& Resource : ResourceSound)
	{
		if (Resource.LoadedResource)
		{
			USoundBase* sCloseDoor = Cast<USoundBase>(ResourceSound[0].LoadedResource);
			USoundBase* sOpenSound = Cast<USoundBase>(ResourceSound[1].LoadedResource);		
		
			if (OpenDoorSound && sCloseDoor)
			{
				OpenDoorSound = sOpenSound;
				CloseDoorSound = sCloseDoor;
			}			
		}
	}





}


void AWoodDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWoodDoor::Interact()
{
}

void AWoodDoor::OpenDoor(float Value)
{
}

void AWoodDoor::DoorOnsameSide()
{

}


