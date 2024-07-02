// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "damage.generated.h"

UENUM()
enum class EDamageType : uint64
{
	DMG_GENERIC         = 1 << 0 ,    /**< Non-specific damage. */
	DMG_CRUSH           = 1 << 1,    /**< Being crushed by something heavy. */
	DMG_BULLET          = 1 << 2,    /**< Shot by a gun. */
	DMG_SLASH           = 1 << 3,    /**< Cutting, from swords or knives. */
	DMG_BURN            = 1 << 4,    /**< Short flame, or on-fire type damage. */
	DMG_VEHICLE         = 1 << 5,    /**< Vehicle ramming into you at speed. */
	DMG_FALL            = 1 << 6,    /**< Fall damage. */
	DMG_EXPLODE         = 1 << 7,    /**< Firer explosion damage. */
	DMG_ELECTRO         = 1 << 8,    /**< Electric shock damage. */
	DMG_ENERGYBEAM      = 1 << 9,    /**< Energy beam damage. */
	DMG_DROWN           = 1 << 10,   /**< Drown damage, gets restored over time. */
	DMG_PARALYZE        = 1 << 11,   /**< Parallelization damage. */
	DMG_NERVEGAS        = 1 << 12,   /**< Toxins to the nerve, special effect? */
	DMG_POISON          = 1 << 13,   /**< Poisonous damage. Similar to nerves? */
	DMG_RADIATION       = 1 << 14,   /**< Radiation damage. Geiger counter go brr. */
	DMG_DROWNRECOVER    = 1 << 15,   /**< Health increase from drown recovery. */
	DMG_CHEMICAL        = 1 << 16,   /**< Chemical damage. */
	DMG_SLOWBURN        = 1 << 17,   /**< Slow burning, just like burning but different rate. */
	DMG_SKIP_ARMOR      = 1 << 18,   /**< This damage will skip armor checks entirely. */
	DMG_SKIP_RAGDOLL    = 1 << 19    /**< This damage will not affect ragdolls. */

};

ENUM_CLASS_FLAGS(EDamageType)


/* damage multiplay for character */
UENUM(BlueprintType, meta=(ScriptName = "EBodyType"))
enum class EBodyPart : uint8
{
	DEFAULT				UMETA(DisplayName = "Default"),
	HEAD				UMETA(DisplayName = "Head"), 
	BODY				UMETA(DisplayName = "Body"),
	LEG					UMETA(DisplayName = "Leg"),
	HAND				UMETA(DisplayName = "Hand"),
};




UCLASS(Config=Game, meta=(ScriptName = "CustomDamageType"))
class JOBSGAME_API Udamage : public UObject
{
	GENERATED_BODY()


};
