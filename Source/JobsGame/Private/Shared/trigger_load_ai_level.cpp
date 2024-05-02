// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/trigger_load_ai_level.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyCharacter.h"

class AMyCharacter;
// Sets default values
Atrigger_load_ai_level::Atrigger_load_ai_level()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Trigger->SetWorldScale3D(FVector(8.5f, 1, 6.25));

}

// Called when the game starts or when spawned
void Atrigger_load_ai_level::BeginPlay()
{
	Super::BeginPlay();
		
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &Atrigger_load_ai_level::OnDetectionLevelBeginOverlap);

}

void Atrigger_load_ai_level::OnDetectionLevelBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const AMyCharacter* LoadLevelCharacter = Cast<const AMyCharacter>(OtherActor);
	if (LoadLevelCharacter != nullptr)
	{
		UGameplayStatics::OpenLevel(this, Level_Name);
		UE_LOG(LogCollision, Warning, TEXT("Load Level: %s"), *Level_Name.ToString());
	}
	
	
}



