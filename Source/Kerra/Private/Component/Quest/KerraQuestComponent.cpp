// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Quest/KerraQuestComponent.h"

#include "KerraGameplayTags.h"
#include "Blueprint/UserWidget.h"
#include "Player/KerraPlayerController.h"
#include "Component/Inventory/KerraInventoryComponent.h"
#include "KerraFunctionLibrary.h"
#include "Interface/KerraInventoryInterface.h"
#include "Kerra/Kerra.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/KerraHUD.h"
#include "UI/Widget/Overlay/KerraOverlayWidget.h"

void UKerraQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	KerraPC = GetOwningController<AKerraPlayerController>();
	
	/*if(UKerraInventoryComponent* InventoryComp = UKerraFunctionLibrary::NativeGetKerraInventoryComponentFromActor(GetOwner()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Bind OnChangedItemCount"));
		//InventoryComp->OnChangeItemCount.AddDynamic(this, )
	}*/
}

bool UKerraQuestComponent::AddQuest(FGameplayTag QuestIDTagToAdd)
{
	/* Add Quest in 'AcceptedQuests' */
	/*
	 * 1. check quest is possible accepted (already accepted, completed, repeatable)?
	 * 2. Add to quest tracking widget
	 */
	FKerraQuestData FoundQuestData = UKerraFunctionLibrary::GetQuestDataByTagFromKerraGI(QuestIDTagToAdd, GetOwner());
	if(!FoundQuestData.QuestID.IsValid())
	{
		KERRALOG(Warning, TEXT("Not valid quest %s"), *FoundQuestData.QuestID.ToString())
		return false;
	}

	AcceptedQuests.AddTag(FoundQuestData.QuestID);
	AcceptedQuestsMap.Add(QuestIDTagToAdd, FoundQuestData);
	ActiveQuest = FoundQuestData;
	AddQuestNotification(EQuestNotification::NewQuest, FoundQuestData);
	return true;

}

void UKerraQuestComponent::AddQuestNotification(EQuestNotification Notification, FKerraQuestData& QuestInfo)
{
	/* if add quest, notify to widget using delegate broadcast */
	AKerraHUD* KerraHUD = UKerraFunctionLibrary::NativeGetKerraHUD(KerraPC);
	checkf(KerraHUD, TEXT("Invalid KerraHUD"));

	KerraHUD->GetPlayerOverlayWidget()->AddQuestNotifyWindow(Notification);
	OnAddQuest.Broadcast(QuestInfo);
}

void UKerraQuestComponent::ClearQuest(FGameplayTag QuestTagToClear)
{
	/*
	 * TODO
	 * receive reward, xp, etc...
	 * notify to widget
	 */
	if(AcceptedQuests.HasTagExact(QuestTagToClear) && AcceptedQuestsMap.Contains(QuestTagToClear))
	{
		CompletedQuests.AddTag(QuestTagToClear);
		CompletedQuestsMap.Add(QuestTagToClear, AcceptedQuestsMap[QuestTagToClear]);
		
		AcceptedQuests.RemoveTag(QuestTagToClear);
		AcceptedQuestsMap.Remove(QuestTagToClear);

		UE_LOG(LogTemp, Warning, TEXT("Clear Quest %s"), *QuestTagToClear.ToString());
		OnCompleteQuest.Broadcast(CompletedQuestsMap[QuestTagToClear]);

		// when clear the quest, require item is subtracted in inventory
		if(UKerraInventoryComponent* TargetInventoryComp = UKerraFunctionLibrary::NativeGetKerraInventoryComponentFromActor(GetOwner()))
		{
			for(const auto Pair : CompletedQuestsMap[QuestTagToClear].RequireObjects)
			{
				TargetInventoryComp->AddItem(Pair.Key, -Pair.Value);
				// TargetInventoryComp->OnChangeItemAmount.Broadcast(Pair.Key, -Pair.Value);
			}
		}

		// TODO: Give rewards
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Player does not have %s quest"), *QuestTagToClear.ToString());
}

bool UKerraQuestComponent::CheckClearCondition(FGameplayTag TagToCheck)
{
	UKerraInventoryComponent* InventoryComp = UKerraFunctionLibrary::NativeGetKerraInventoryComponentFromActor(GetOwner());
	checkf(InventoryComp, TEXT("Not valid inventory component"));

	if(!AcceptedQuests.HasTagExact(TagToCheck))
	{
		UE_LOG(LogTemp, Warning, TEXT("Not in accepted quest (%s)"), *TagToCheck.ToString());
		return false;
	}
	
	FKerraQuestData TargetQuest = AcceptedQuestsMap[TagToCheck];
	for(const auto Pair : TargetQuest.RequireObjects)
	{
		if(InventoryComp->GetCurrentItemCount(Pair.Key) < Pair.Value)
		{
			return false;
		}
	}
	return true;
}

float UKerraQuestComponent::CheckQuestProgress(FGameplayTag QuestTagToCheck, FGameplayTag ObjectTag)
{
	if(!AcceptedQuests.HasTagExact(QuestTagToCheck))
	{
		UE_LOG(LogTemp, Warning, TEXT("Do not check %s quest"), *QuestTagToCheck.ToString());
		return -1.f;
	}

	if(!AcceptedQuestsMap[QuestTagToCheck].RequireObjects.Contains(ObjectTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s item not require in %s quest"), *ObjectTag.ToString(), *QuestTagToCheck.ToString());
		return -1.f;
	}

	float QuestProgressRatio = 0.f;
	float RequireObjectsNum = static_cast<float>(AcceptedQuestsMap[QuestTagToCheck].RequireObjects.Num());

	IKerraInventoryInterface* InventoryInterface = Cast<IKerraInventoryInterface>(GetOwner());
	UKerraInventoryComponent* InventoryComponent = InventoryInterface->GetKerraInventoryComponent();

	for(const auto Pair : AcceptedQuestsMap[QuestTagToCheck].RequireObjects)
	{
		float CurrentObjectAmount = static_cast<float>(FMath::Clamp(InventoryComponent->GetCurrentItemCount(Pair.Key), 0, Pair.Value));
		float CurrentRatio = CurrentObjectAmount < static_cast<float>(Pair.Value) ? (CurrentObjectAmount / static_cast<float>(Pair.Value)) : 1.f;
		CurrentRatio /= RequireObjectsNum;
		QuestProgressRatio += CurrentRatio;
	}
	return QuestProgressRatio;
}

bool UKerraQuestComponent::GiveRewards(FGameplayTag QuestTag)
{
	if(FKerraQuestData* QuestInfo = QuestDataTable->FindRow<FKerraQuestData>(QuestTag.GetTagName(), ""))
	{
		UKerraInventoryComponent* InventoryComponent = UKerraFunctionLibrary::NativeGetKerraInventoryComponentFromActor(GetOwner());
		checkf(InventoryComponent, TEXT("Not Value Inventory Component"));
		
		if(QuestInfo->QuestReward.GiveXP > 0)
		{
			// Give XP
		}

		if(QuestInfo->QuestReward.GiveGold > 0)
		{
			// Give Gold
			InventoryComponent->AddGold(QuestInfo->QuestReward.GiveGold);
		}

		if(QuestInfo->QuestReward.GiveItem.Num() != 0)
		{
			for(const auto Pair: QuestInfo->QuestReward.GiveItem)
			{
				InventoryComponent->AddItem(Pair.Key, Pair.Value);
			}
		}
		return true;
	}
	return false;
}
