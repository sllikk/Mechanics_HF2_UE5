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

	pdebug_entity = ObjectInitializer.CreateDefaultSubobject<Udebug_entity>(this, TEXT("debug-entity"));	
	pdebug_entity->SetDebugEntity(this);
	pdebug_entity->SetDebugMesh(StaticMeshComponent);
	pdebug_entity->SetDebugHealth(100);

	State = ECubeState::IDLE;
	
	Debug = pdebug_entity->GetEnumValueAsString("ECubeState", static_cast<int32>(State));
	pdebug_entity->SetDebugEnumAsString(Debug);

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

	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetSimulatePhysics(true);
		StaticMeshComponent->SetNotifyRigidBodyCollision(true);
		StaticMeshComponent->SetMassOverrideInKg(NAME_Name, 50, true);
		StaticMeshComponent->OnComponentHit.AddDynamic(this, &Aai_cube::OnHit);
		
	}
	
}


// Called every frame
void Aai_cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void Aai_cube::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	
	const float ImaxStress = NormalImpulse.Size();
	pdebug_entity->SetDebugStress(ImaxStress);
	
}

