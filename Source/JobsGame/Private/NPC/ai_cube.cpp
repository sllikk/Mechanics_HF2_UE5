// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/ai_cube.h"

#include "AIController.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"


// Sets default values
Aai_cube::Aai_cube(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.Get())
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, "StaticMesh");
	RootComponent = StaticMeshComponent;

	const FSoftObjectPath ObjectPath(TEXT("/Game/LevelPrototyping/Meshes/Prototype"));
	static TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	if (ObjectPath.IsValid())
	{
		StaticMesh = Cast<UStaticMesh>(ObjectPath.TryLoad());
	}
	if (StaticMesh != nullptr)
	{
		StaticMeshComponent->SetStaticMesh(StaticMesh);
	}
	
	PerceptionStimuliSourceComponent = ObjectInitializer.CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(this, "PerceptionComponent");
	PerceptionStimuliSourceComponent->bAutoRegister = true;

	
}

void Aai_cube::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (PerceptionStimuliSourceComponent)
	{
		PerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
		PerceptionStimuliSourceComponent->RegisterWithPerceptionSystem();

	}
}

// Called when the game starts or when spawned
void Aai_cube::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Aai_cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

