// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/test_props.h"

#include "Engine/StaticMeshActor.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/MyCharacter.h"

// Sets default values
Atest_props::Atest_props()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("box_trigger"));	
	RootComponent = BoxTrigger;
	is_spawn = false;
	
}

// Called when the game starts or when spawned
void Atest_props::BeginPlay()
{
	Super::BeginPlay();
	
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &Atest_props::OnOverlapBegin);
}

// Called every frame
void Atest_props::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Atest_props::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		AMyCharacter* TriggerPlayer = Cast<AMyCharacter>(OtherActor);

		if (TriggerPlayer != nullptr)
		{
			UE_LOG(LogCollision, Warning, TEXT("Trigger: %s"), *OtherActor->GetName())
			SpawnObject();

		}
	}
}

void Atest_props::SpawnObject() const
{
	if (ArrayMeshComponents.Num() == 0) return;
	
	FVector const& Origin = BoxTrigger->GetComponentLocation();
	FVector const& Extern = BoxTrigger->GetScaledBoxExtent();
	
	for (UStaticMesh* SpawnMesh : ArrayMeshComponents)
	{
		const FVector& SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extern);
		const FRotator& SpawnRotator = FRotator::ZeroRotator;
		FActorSpawnParameters SpawnParameters;

		for (uint8 i  = 0; i < 5; ++i)
		{
			AStaticMeshActor* NewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnLocation, SpawnRotator, SpawnParameters);
			if (NewActor != nullptr)
			{
				NewActor->SetMobility(EComponentMobility::Movable);
				NewActor->GetStaticMeshComponent()->SetStaticMesh(SpawnMesh);
				NewActor->GetStaticMeshComponent()->SetSimulatePhysics(true);
			}	
		}
	}
}

