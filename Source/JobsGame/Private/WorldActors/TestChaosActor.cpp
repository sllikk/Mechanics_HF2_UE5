// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/TestChaosActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "WorldActors/BatteryKit.h"
#include "WorldActors/HealthKit.h"

// Sets default values
ATestChaosActor::ATestChaosActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GeometryCollectionComponent = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GC"));

	
	const FSoftObjectPath FindGC(TEXT("/Game/GC/GC_SupplyCrate"));
	static UGeometryCollection* LoadGeometry = nullptr;
    if (FindGC.IsValid())
    {
	    LoadGeometry = Cast<UGeometryCollection>(FindGC.TryLoad());
    }
    if (LoadGeometry != nullptr)
    {
    	GeometryCollectionComponent->SetRestCollection(LoadGeometry);
    	RootComponent = GeometryCollectionComponent; 
    }
    else
    {
		UE_LOG(LogLoad, Warning, TEXT("Error Load: %s"), *FindGC.ToString());
    }


	// Загрузка Blueprint класса для разрушения
	static ConstructorHelpers::FClassFinder<AActor> DestructionBPClass(TEXT("/Game/GC/Impact"));
	if (DestructionBPClass.Class != nullptr)
	{
		DestructionBlueprint = DestructionBPClass.Class;
	}
	
	MaxHealth = 25.0f;
	
}

// Called when the game starts or when spawned
void ATestChaosActor::BeginPlay()
{
	Super::BeginPlay();

	GeometryCollectionComponent->OnComponentHit.AddDynamic(this, &ATestChaosActor::OnComponentHit);
	GeometryCollectionComponent->SetMassOverrideInKg(NAME_None, 60.0f);

	Debug();
	

}

// Called every frame
void ATestChaosActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Debug();

}


void ATestChaosActor::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (NormalImpulse.Size() >= 10000.0f)
	{
		float Damage = 1;
		
		ApplyDamage(Damage,  Hit.Location);
	}
	if (spawn)
	{
		GeometryCollectionComponent->OnComponentHit.RemoveAll(this);
	}
}


void ATestChaosActor::ApplyDamage(float Damage, FVector HitDamage)
{
		DestroyBox(HitDamage);
}


void ATestChaosActor::DestroyBox(FVector HitLocation)
{
	if (GeometryCollectionComponent)
	{
		SpawnDestructionActor(HitLocation);
		// Спавним предметы из разрушенной коробки
		SpawnProps(GeometryCollectionComponent->Bounds.Origin);
	}
}


void ATestChaosActor::SpawnDestructionActor(FVector SpawnLocation)
{
	if (DestructionBlueprint != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AActor>(DestructionBlueprint, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
		spawn = true;
	}
}


void ATestChaosActor::Debug()
{
	FString String = FString::Printf(TEXT("Health: %2.f"), MaxHealth);
	FVector Location = GetActorLocation();	
	DrawDebugString(GetWorld(), Location, String, nullptr, FColor::White, -1);
	

}


void ATestChaosActor::SpawnProps(FVector HitLocation)
{
	const int16 MAXSPAWN = 3;

	TArray<TSubclassOf<AActor>> ItemClasses;
	ItemClasses.Add(AHealthKit::StaticClass());
	ItemClasses.Add(ABatteryKit::StaticClass());

	for (int16 i = 0; i < MAXSPAWN; i++)
	{
		if (ItemClasses.Num() > 0)
		{
			int16 ItemIndex = FMath::RandRange(0, ItemClasses.Num() - 1);
			TSubclassOf<AActor> SpawnActor = ItemClasses[ItemIndex];	

			GetWorld()->SpawnActor<AActor>(SpawnActor, HitLocation, FRotator::ZeroRotator);

		}
	}

	
}
