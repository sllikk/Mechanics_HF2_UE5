// Fill out your copyright notice in the Description page of Project Settings.


#include "Property/debug_entity.h"


// Sets default values for this component's properties
Udebug_entity::Udebug_entity(): DebugInfo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Udebug_entity::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void Udebug_entity::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UpdateDebug();

	
}


void Udebug_entity::UpdateDebug() const
{	const FString& DEBUG = FString::Printf(TEXT("Name: %s\n"
										   "Model: %s\n"
										    "State: %s\n"
										   "Position: %s\n"
										   "Rotation: %s\n"
										   "Mass: %.2f\n"
										   "Stress: %.2f\n"
										   "Health: %d\n"),
											
										*DebugInfo.Entity->GetName(),
									   *DebugInfo.debug_mesh->GetName(),
									   *DebugInfo.EnumAsString,		
									   *FString(DebugInfo.debug_mesh->GetComponentLocation().ToString()),
									   *FString(DebugInfo.debug_mesh->GetComponentRotation().ToString()),
									   DebugInfo.debug_mesh->GetMass(),
									   DebugInfo.flstressEntity, 	
									   DebugInfo.ihealth);
	//const FColor& ColorDebug = FColor::Silver;														
	DrawDebugString(GetWorld(), DebugInfo.debug_mesh->GetComponentLocation(), DEBUG, nullptr, FColor::Silver, 0, true);		


}

FString Udebug_entity::GetEnumValueAsString(const FString& EnumName, int32 EnumValue)
{
	const UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
	if(!pEnum) return FString("Invalid");

	return pEnum->GetNameStringByIndex(EnumValue);
}


