// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Inventory/KerraInventoryComponent.h"

void UKerraInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UKerraInventoryComponent::AddItem(FGameplayTag ItemID, int32 AddCount)
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
		OwningItemMaps[ItemID].CurrentCount += AddCount;
		
		// OnAddItem.Broadcast(ItemID); // current not used

		if(!ItemToAdd->AppliedQuest.IsEmpty())
		{
			// Broadcast to WBP_TrackingQuest, WBP_TrackingQuestText, WBP_QuestWindow 
			OnChangeItemCount.Broadcast(ItemID, OwningItemMaps[ItemID].CurrentCount);	
		}
		return true;
	}
	return false;
}

int32 UKerraInventoryComponent::GetCurrentItemCount(FGameplayTag ItemIDTag)
{
	if(OwningItemMaps.Find(ItemIDTag))
	{
		return OwningItemMaps[ItemIDTag].CurrentCount;
	}
	return 0;
}
