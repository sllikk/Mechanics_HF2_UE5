// Fill out your copyright notice in the Description page of Project Settings.

#include "Property/CustomDamage.h"

DEFINE_LOG_CATEGORY(LogCustomDamage)

UCustomDamage::UCustomDamage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), DamageType()
{
	InitialDamageType();

}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

void UCustomDamage::InitialDamageType()
{
	DataType.Add(EDamageType::DMG_BURN, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_FALL, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_CRUSH, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_DROWN, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_BULLET, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_SLASH, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_POISON, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_ELECTRO, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_EXPLODE, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_GENERIC, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_CHEMICAL, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_VEHICLE, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_NERVEGAS, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_PARALYZE, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_SLOWBURN, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_RADIATION, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_SKIP_ARMOR, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_SKIP_RAGDOLL, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_ENERGYBEAM, FDamageTypeData{0, 0});
	DataType.Add(EDamageType::DMG_DROWNRECOVER, FDamageTypeData{0, 0});
}


FDamageTypeData UCustomDamage::GetDamageTypeData() const
{
	const FDamageTypeData* Data = DataType.Find(DamageType);
	return Data ? *Data : FDamageTypeData();
	
}

//------------------------------------------------------------------------------------
	//              Func Damage
//------------------------------------------------------------------------------------

EDamageType UCustomDamage::GetCurrentDamageType() const
{
	return DamageType;
}



void UCustomDamage::SetCurrentDamageType(EDamageType TypeDamage)
{
	DamageType = TypeDamage;
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

void UCustomDamage::AddDamage(float flAddAmount)
{
	m_flDamage += flAddAmount;
}


AActor* UCustomDamage::GetAttack() const
{	
	return m_Attacker;
}

void UCustomDamage::SetAttacker(AActor* pAttacker)
{
	m_Attacker = pAttacker;	
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------


float UCustomDamage::GetDamage() const
{
	return m_flDamage;
}
//------------------------------------------------------------------------------------

void UCustomDamage::SetDamage(float flDamage)
{
	m_flDamage = flDamage; 
}
//------------------------------------------------------------------------------------

float UCustomDamage::GetMaxDamage() const
{
	return m_flMaxDamage;
}
//------------------------------------------------------------------------------------

void UCustomDamage::SetMaxDamage(float flMaxDamage)
{
	m_flMaxDamage = flMaxDamage;  
}
//------------------------------------------------------------------------------------

void UCustomDamage::ScaleDamage(float flScaleAmount)
{
	m_flDamage *= flScaleAmount;
}
//------------------------------------------------------------------------------------

void UCustomDamage::SubtractDamage(float flSubtractAmount)
{
	m_flDamage -= flSubtractAmount;
}
//------------------------------------------------------------------------------------

FVector UCustomDamage::GetDamageForce() const
{
	return m_vecDamageForce;
}
//------------------------------------------------------------------------------------

void UCustomDamage::SetDamageForce(const FVector& damageForce)
{
	m_vecDamageForce = damageForce;	
}
//------------------------------------------------------------------------------------

void UCustomDamage::ScaleDamageForce(float flScaleAmount)
{
	m_vecDamageForce *= flScaleAmount;	
}
//------------------------------------------------------------------------------------

float UCustomDamage::GetDamageForForceCalc() const
{
	return m_flDamageForForce;
}
//------------------------------------------------------------------------------------

void UCustomDamage::SetDamageForForceCalc(float flDamage)
{
	m_flDamageForForce = flDamage;
}
//------------------------------------------------------------------------------------

FVector UCustomDamage::GetDamagePosition() const
{
	return m_vecDamagePosition; 
}
//------------------------------------------------------------------------------------

void UCustomDamage::SetDamagePosition(const FVector& damagePosition)
{
	m_vecDamagePosition = damagePosition;
}
//------------------------------------------------------------------------------------

FVector UCustomDamage::GetReportedPosition() const
{
	return m_vecReportedPosition;
}
//------------------------------------------------------------------------------------

void UCustomDamage::SetReportedPosition(const FVector& reportedPosition)
{
	m_vecReportedPosition = reportedPosition;
}


