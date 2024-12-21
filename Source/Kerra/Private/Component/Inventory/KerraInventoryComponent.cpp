// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Inventory/KerraInventoryComponent.h"

void UKerraInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UKerraInventoryComponent::AddItem(FGameplayTag ItemID)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ItemID.GetTagName().ToString());
	checkf(ItemDataTable, TEXT("Not valid Item Data Table in inventory"));
	
	if (FKerraItemInfo* ItemToAdd = ItemDataTable->FindRow<FKerraItemInfo>(ItemID.GetTagName(), ""))
	{
		OwningItemTags.AddTag(ItemID);

		if(!OwningItemMaps.Contains(ItemID))
		{
			OwningItemMaps.Add(ItemID, *ItemToAdd);
		}
		OwningItemMaps[ItemID].CurrentCount++;

		if(OnAddItem.IsBound())
		{
			OnAddItem.Broadcast(ItemID);
		}
		return true;
	}
	return false;
}
