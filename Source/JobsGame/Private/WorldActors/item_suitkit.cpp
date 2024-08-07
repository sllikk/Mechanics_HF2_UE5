// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/item_suitkit.h"

#include "Kismet/GameplayStatics.h"
#include "Player/MyCharacter.h"

Aitem_suitkit::Aitem_suitkit()
{
	suitkit_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	suitkit_mesh->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
	suitkit_mesh->ComponentTags.Add(FName("PhysicsObject"));
	RootComponent = suitkit_mesh;

	const FSoftObjectPath FindMesh(TEXT("/Game/WorldActors/RestoreKits/SuitKit/suit_kit"));
	static TObjectPtr<UStaticMesh> LoadMesh = nullptr;

	if (FindMesh.IsValid())
	{
		LoadMesh = Cast<UStaticMesh>(FindMesh.TryLoad());
	}
	if (LoadMesh != nullptr)
	{
		suitkit_mesh->SetStaticMesh(LoadMesh);	
	}

	SetSoundTouchSound(LoadObject<USoundBase>(nullptr, TEXT("/Game/Sound/ActorSound/Cue/Pickup_Battery_Cue")));
	
	SetRadiusSphere(1000.0f);
	SetBaseStaticMeshComponent(suitkit_mesh);
	GetTriggerCollision()->SetupAttachment(suitkit_mesh);
	GetTriggerCollision()->SetWorldLocation(FVector(0, 0, 500));
	GetTriggerCollision()->InitSphereRadius(GetSphereRadius());
	SetMassObj(12.0f);	
}

void Aitem_suitkit::BeginPlay()
{
	Super::BeginPlay();
}

void Aitem_suitkit::OnTouch(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnTouch(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

constexpr uint8 UE_SUIT_AMOUNTH = 15;
void Aitem_suitkit::Use(AActor* pCharacterUse)
{
	Super::Use(pCharacterUse);

	ptrPlayer = Cast<AMyCharacter>(pCharacterUse);

	if (ptrPlayer != nullptr)
	{
		if (ptrPlayer->GetSuitCharger() < ptrPlayer->GetSuitMaxCharger())
		{
			ptrPlayer->RestoreSuit(UE_SUIT_AMOUNTH);	

			if (GetSoundTouch() != nullptr)
			{
				SetUse(true);
				UGameplayStatics::PlaySoundAtLocation(this, GetSoundTouch(), GetActorLocation());
			}
		}
	}

	
}
