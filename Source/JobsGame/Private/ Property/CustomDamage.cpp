// Fill out your copyright notice in the Description page of Project Settings.

#include " Property/CustomDamage.h"

DEFINE_LOG_CATEGORY(LogCustomDamage);

UCustomDamage::UCustomDamage()
{
	// Initialize the dictionary with default values for each damage type
	DamageData.Add(EDamageType::DMG_FIRE, FDamageTypeData{1.0f, 0.0f});
	DamageData.Add(EDamageType::DMG_ELECTRIC, FDamageTypeData{2.0f, 0.0f});
	DamageData.Add(EDamageType::DMG_FALL, FDamageTypeData{10.0f, 0.0f});
	DamageData.Add(EDamageType::DMG_DROWN, FDamageTypeData{5.0f, 0.0f});
	DamageData.Add(EDamageType::DMG_WEAPON, FDamageTypeData{5.0f, 0.0f});
	DamageData.Add(EDamageType::DMG_PHYSICS, FDamageTypeData{5.0f, 0.0f});
	DamageData.Add(EDamageType::DMG_EXPLOSION, FDamageTypeData{30.0f, 0.0f});
	

}

// Get data for the current damage type
FDamageTypeData UCustomDamage::GetDamageTypeData() const
{
	const FDamageTypeData* Data = DamageData.Find(DamageType);
	return Data ? *Data: FDamageTypeData();
}
