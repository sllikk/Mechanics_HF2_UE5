// Fill out your copyright notice in the Description page of Project Settings.


#include "Property/shell_pool.h"
#include "Shared/Shell.h"

Ashell_pool::Ashell_pool()
{
	imaxpool = 50;
}

void Ashell_pool::BeginPlay()
{
	Super::BeginPlay();

	InitializePool(AShell::StaticClass(), imaxpool);	

}
