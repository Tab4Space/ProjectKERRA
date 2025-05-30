// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Inventory/KerraInventoryComponent.h"

#include "KerraGameplayTags.h"
#include "KerraFunctionLibrary.h"
#include "Game/KerraGameInstance.h"
#include "Kismet/GameplayStatics.h"

UKerraInventoryComponent::UKerraInventoryComponent()
{
	/*OwningItemTags.AddTag(KerraGameplayTags::Item_ID_1Apple);
	OwningItemMaps.Add(KerraGameplayTags::Item_ID_1Apple, FKerraItemData());
	OwningItemMaps[KerraGameplayTags::Item_ID_1Apple].CurrentAmount = 100;*/
}

void UKerraInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	/* TODO: Init inventory list from save file and set init flag. ex) IsInitialized */
}

bool UKerraInventoryComponent::AddItem(FGameplayTag ItemIDTag, int32 AddAmount)
{
	if(OwningItemTags.HasTagExact(ItemIDTag))
	{
		/* already has item in inventory */
		if(OwningItemMaps[ItemIDTag].bStackable)
		{
			OwningItemMaps[ItemIDTag].CurrentAmount += AddAmount;
			if(OwningItemMaps[ItemIDTag].CurrentAmount <= 0)
			{
				OnChangeItemAmount.Broadcast(ItemIDTag, OwningItemMaps[ItemIDTag].CurrentAmount);
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

		/* just change amount*/
		if(OwningItemMaps.Contains(ItemIDTag))
		{
			OnChangeItemAmount.Broadcast(ItemIDTag, OwningItemMaps[ItemIDTag].CurrentAmount);
		}
		return true;
	}

	/* add new item in inventory */
	FKerraItemData ItemDataToAdd = UKerraFunctionLibrary::GetItemDataByTagFromKerraGI(ItemIDTag, GetOwner());
	//if (FKerraItemData* ItemToAdd = ItemDataTable->FindRow<FKerraItemData>(ItemIDTag.GetTagName(), ""))
	if (ItemDataToAdd.IsValid())
	{
		OwningItemTags.AddTag(ItemIDTag);
		OwningItemMaps.Add(ItemIDTag, ItemDataToAdd);
		OwningItemMaps[ItemIDTag].CurrentAmount += AddAmount;

		OnChangeItemAmount.Broadcast(ItemIDTag, OwningItemMaps[ItemIDTag].CurrentAmount);
		
		// OnAddItem.Broadcast(ItemID); // current not used
		// check this item is applied quest or not.
		/*if(!ItemToAdd->AppliedQuest.IsEmpty())
		{
			// Broadcast to WBP_TrackingQuest, WBP_TrackingQuestText, WBP_QuestWindow 
			OnChangeItemAmount.Broadcast(ItemIDTag, OwningItemMaps[ItemIDTag].CurrentAmount);
		}*/
		return true;
	}
	return false;
}

void UKerraInventoryComponent::AddGold(int32 AddAmount)
{
	CurrentGolds = FMath::Clamp(CurrentGolds, 0, CurrentGolds+=AddAmount);
	OnChangeGold.Broadcast(CurrentGolds);
	UE_LOG(LogTemp, Warning, TEXT("Current Gold: %d"), CurrentGolds);
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
	return FMath::Clamp(CurrentGolds, 0, CurrentGolds);
}
