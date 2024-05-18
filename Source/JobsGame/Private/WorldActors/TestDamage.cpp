// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/TestDamage.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyCharacter.h"
#include "Property/CustomDamage.h"

// Sets default values
ATestDamage::ATestDamage()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));	
	RootComponent = StaticMeshComponent;
	
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Collision->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void ATestDamage::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ATestDamage::Damaged);
}

// Called every frame
void ATestDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestDamage::Damaged(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		const AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
		if (Character != nullptr)
		{
			UCustomDamage* CustomDamage = NewObject<UCustomDamage>();
			if ( CustomDamage != nullptr )
			{
				CustomDamage->SetCurrentDamageType( EDamageType::DMG_BURN );	
				CustomDamage->SetDamage( 12 );
				UGameplayStatics::ApplyDamage(OtherActor, CustomDamage->GetDamage(), nullptr, this, CustomDamage->StaticClass());
			}
		}
	}
}		
	

