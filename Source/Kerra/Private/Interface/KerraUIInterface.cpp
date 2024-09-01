// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/KerraUIInterface.h"

// Add default functionality here for any IKerraUIInterface functions that are not pure virtual.
UKerraPlayerUIComponent* IKerraUIInterface::GetPlayerUIComponent() const
{
	return nullptr;
}

UKerraEnemyUIComponent* IKerraUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}
