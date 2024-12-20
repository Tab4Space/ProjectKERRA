// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Inventory/KerraInventoryComponent.h"

void UKerraInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UKerraInventoryComponent::AddItem(FGameplayTag ItemID)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ItemID.GetTagName().ToString());

	return false;
}
