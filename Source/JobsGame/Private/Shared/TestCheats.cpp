// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/TestCheats.h"

void UTestCheats::ForceGarbageCollection()
{
	GEngine->ForceGarbageCollection(true);
}
