// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "damage.generated.h"


/** All available damage types. */
UENUM(BlueprintType, meta=(ScriptName = "EDamageType"))
enum class EDamageType
{

	DMG_GENERIC							UMETA(DisplayName = "GenericDamage"),												/**< Non-specific damage. */
	DMG_CRUSH							UMETA(DisplayName = "CrushDamage"),												/**< Being crushed by something heavy. */
    DMG_BULLET							UMETA(DisplayName = "BulletDamage"),												/**< Shot by a gun. */
    DMG_SLASH							UMETA(DisplayName = "SlashDamage"),												/**< Cutting, from swords or knives. */
    DMG_BURN							UMETA(DisplayName = "BurnDamage"),												/**< Short flame, or on-fire type damage. */
    DMG_VEHICLE							UMETA(DisplayName = "VenicleDamage"),												/**< Vehicle ramming into you at speed. */
    DMG_FALL							UMETA(DisplayName = "Fall damage"),												/**< Fall damage */
    DMG_EXPLODE							UMETA(DisplayName = "ExplosionDamage"),												/**< Firer explosion damage. */
    DMG_ELECTRO							UMETA(DisplayName = "ElectricDamage"),												/**< Electric shock damage. */
    DMG_ENERGYBEAM						UMETA(DisplayName = "Energy_Beam_Damage"),											/**< Energy beam damage. */
    DMG_DROWN							UMETA(DisplayName = "DrownDamage"),												/**< Drown damage, gets restored over time. */
    DMG_PARALYZE						UMETA(DisplayName = "ParallelizationDamage"),											/**< Parallelization damage. */
    DMG_NERVEGAS						UMETA(DisplayName = "Toxins to the nerve"),											/**< Toxins to the nerve, special effect? */
    DMG_POISON							UMETA(DisplayName = "PoisonousDamage"),												/**< Poisonous damage. Similar to nerves? */
    DMG_RADIATION						UMETA(DisplayName = "RadiationDamage"),												/**< Radiation damage. Geiger counter go brr */
    DMG_DROWNRECOVER					UMETA(DisplayName = "DrownRecovery"),												/**< Health increase from drown recovery. */
    DMG_CHEMICAL						UMETA(DisplayName = "ChemicalDamage"),												/**< Chemical damage. */
    DMG_SLOWBURN						UMETA(DisplayName = "SlowBurn"),												/**< Slow burning, just like burning but different rate. */
    DMG_SKIP_ARMOR						UMETA(DisplayName = "Damage will skip armor "),											/**< This damage will skip armor checks entirely. */
    DMG_SKIP_RAGDOLL					UMETA(DisplayName = "Damage will not affect ragdolls")									    	/**< This damage will not affect ragdolls. */
};


UCLASS(Config=Game, meta=(ScriptName = "CustomDamageType"))
class JOBSGAME_API Udamage : public UObject
{
	GENERATED_BODY()


};
