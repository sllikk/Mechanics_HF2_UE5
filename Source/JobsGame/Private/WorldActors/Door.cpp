// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/Door.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyCharacter.h"

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

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ADoor::OpenDoor);
		Timeline.AddInterpFloat(CurveFloat ,TimelineProgress);
	}
	
	
	
}	


void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
	
}

void ADoor::Interact()
{
	if (blsDoorClossed)
	{
		DoorOnsameSide();
		Timeline.Play();
	
	}
	else
	{
		Timeline.Reverse();
	}
	blsDoorClossed = !blsDoorClossed;
}

void ADoor::OpenDoor(float Value)
{
	// Door Rotate 
	float Angle = blsDoorOnsameSide ? -m_DoorRotateAngle : m_DoorRotateAngle;
	FRotator Rotator = FRotator(0.0f, m_DoorRotateAngle * Value, 0.0f);
	DoorComponent->SetRelativeRotation(Rotator);
}

void ADoor::DoorOnsameSide()
{
	FVector CharacterVector = Character->GetActorForwardVector();
	FVector DoorVector = GetActorForwardVector();
	blsDoorOnsameSide = (FVector::DotProduct(CharacterVector, DoorVector)) >=0;
}

