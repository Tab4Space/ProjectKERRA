// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/KerraWidgetInterface.h"

// Add default functionality here for any IKerraUIInterface functions that are not pure virtual.
UHeroUIComponent* IKerraWidgetInterface::GetPlayerUIComponent() const
{
	return nullptr;
}

UEnemyUIComponent* IKerraWidgetInterface::GetEnemyUIComponent() const
{
	return nullptr;
}
