// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomType/CustomDamage.h"

DEFINE_LOG_CATEGORY(LogCustomDamage);

UCustomDamage::UCustomDamage()
{
	DataType.Add(EDamageType::DMG_FIRE, FDamageTypeData{1.0f, 0.0f});
	DataType.Add(EDamageType::DMG_ELECTRIC, FDamageTypeData{1.0f, 0.0f});
	DataType.Add(EDamageType::DMG_FALL, FDamageTypeData{1.0f, 0.0f});
	DataType.Add(EDamageType::DMG_DROWN, FDamageTypeData{1.0f, 0.0f});
	DataType.Add(EDamageType::DMG_EXPLOSION, FDamageTypeData{1.0f, 0.0f});
	DataType.Add(EDamageType::DMG_PHYSICS, FDamageTypeData{1.0f, 0.0f});
	DataType.Add(EDamageType::DMG_WEAPON, FDamageTypeData{1.0f, 0.0f});
	
}


FDamageTypeData UCustomDamage::GetDamageTypeData() const
{
	const FDamageTypeData* Data = DataType.Find(DamageType);
	return Data ? *Data : FDamageTypeData();

}
