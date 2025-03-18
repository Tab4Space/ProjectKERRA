// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Inventory/KerraInventoryComponent.h"

void UKerraInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UKerraInventoryComponent::AddItem(FGameplayTag ItemIDTag, int32 AddAmount)
{
	checkf(ItemDataTable, TEXT("Not valid Item Data Table in inventory"));
	
	if(OwningItemTags.HasTagExact(ItemIDTag))
	{
		/* already has item in inventory */
		if(OwningItemMaps[ItemIDTag].bStackable)
		{
			OwningItemMaps[ItemIDTag].CurrentAmount += AddAmount;
			if(OwningItemMaps[ItemIDTag].CurrentAmount <= 0)
			{
				OwningItemTags.RemoveTag(ItemIDTag);
				OwningItemMaps.Remove(ItemIDTag);
				UE_LOG(LogTemp, Warning, TEXT("%s is deleted because less than 1EA"), *ItemIDTag.ToString());
			}
		}
		else
		{
			OwningItemMaps[ItemIDTag].CurrentAmount = 1;
			UE_LOG(LogTemp, Warning, TEXT("%s is owned only 1EA"), *ItemIDTag.ToString());
		}

		if(OwningItemMaps.Contains(ItemIDTag))
		{
			OnChangeItemAmount.Broadcast(ItemIDTag, OwningItemMaps[ItemIDTag].CurrentAmount);	
		}
		return true;
	}

	/* add new item in inventory */
	if (FKerraItemInfo* ItemToAdd = ItemDataTable->FindRow<FKerraItemInfo>(ItemIDTag.GetTagName(), ""))
	{
		OwningItemTags.AddTag(ItemIDTag);
		OwningItemMaps.Add(ItemIDTag, *ItemToAdd);
		OwningItemMaps[ItemIDTag].CurrentAmount += AddAmount;
		
		// OnAddItem.Broadcast(ItemID); // current not used
		if(!ItemToAdd->AppliedQuest.IsEmpty())
		{
			// Broadcast to WBP_TrackingQuest, WBP_TrackingQuestText, WBP_QuestWindow 
			OnChangeItemAmount.Broadcast(ItemIDTag, OwningItemMaps[ItemIDTag].CurrentAmount);	
		}
		return true;
	}
	return false;
}

void UKerraInventoryComponent::AddGold(int32 AddAmount)
{
	Golds = FMath::Clamp(Golds, 0, Golds+=AddAmount);
	UE_LOG(LogTemp, Warning, TEXT("Current Gold: %d"), Golds);
}

FGameplayTagContainer UKerraInventoryComponent::GetOwningItemTags()
{
	// Return owning all item tags
	return OwningItemTags;
}

int32 UKerraInventoryComponent::GetCurrentItemCount(FGameplayTag ItemIDTag)
{
	if(OwningItemMaps.Find(ItemIDTag))
	{
		return OwningItemMaps[ItemIDTag].CurrentAmount;
	}
	return 0;
}

int32 UKerraInventoryComponent::GetCurrentGold()
{
	return FMath::Clamp(Golds, 0, Golds);
}
