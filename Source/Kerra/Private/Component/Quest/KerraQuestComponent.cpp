// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Quest/KerraQuestComponent.h"

#include "KerraGameplayTags.h"
#include "Blueprint/UserWidget.h"
#include "Player/KerraPlayerController.h"
#include "Widget/KerraWidgetBase.h"
#include "Component/Inventory/KerraInventoryComponent.h"
#include "KerraFunctionLibrary.h"

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

void UKerraQuestComponent::ToggleQuestWidget()
{
	if(!IsValid(QuestWidget))
	{
		QuestWidget = CreateWidget<UKerraWidgetBase>(KerraPC, QuestWidgetClass);
		QuestWidget->AddToViewport();
		QuestWidget->SetVisibility(ESlateVisibility::Visible);
		
		KerraPC->SetShowMouseCursor(true);
		KerraPC->SetInputMode(FInputModeGameAndUI());
		bShowQuestWindow = true;
	}
	else
	{
		if(bShowQuestWindow)
		{
			QuestWidget->SetVisibility(ESlateVisibility::Hidden);
			KerraPC->SetShowMouseCursor(false);
			KerraPC->SetInputMode(FInputModeGameOnly());
			bShowQuestWindow = false;
		}
		else
		{
			QuestWidget->SetVisibility(ESlateVisibility::Visible);
			KerraPC->SetShowMouseCursor(true);
			KerraPC->SetInputMode(FInputModeGameAndUI());
			bShowQuestWindow = true;
		}
	}
}

bool UKerraQuestComponent::AddQuest(FGameplayTag QuestIDTagToAdd)
{
	/* Add Quest in 'AcceptedQuests' */
	/*
	 * 1. check quest is possible accepted (already accepted, completed, repeatable)?
	 * 2. Add to quest tracking widget
	 */

	if(FKerraQuestInfo* QuestInfoToAdd = QuestDataTable->FindRow<FKerraQuestInfo>(QuestIDTagToAdd.GetTagName(), ""))
	{
		AcceptedQuests.AddTag(QuestIDTagToAdd);
		AcceptedQuestsMap.Add(QuestIDTagToAdd, *QuestInfoToAdd);
		ActiveQuest = *QuestInfoToAdd;
		AddQuestNotification(EQuestNotification::NewQuest, *QuestInfoToAdd);
		return true;
	}
	return false;
}

void UKerraQuestComponent::AddQuestNotification(EQuestNotification Notification, FKerraQuestInfo& QuestInfo)
{
	/* if add quest, notify to widget using delegate broadcast */
	if(Notification == EQuestNotification::NewQuest)
	{
		QuestNotificationWidget = CreateWidget<UKerraWidgetBase>(KerraPC, QuestNotificationWidgetClass);
		if(OnAddQuest.IsBound())
		{
			OnAddQuest.Broadcast(QuestInfo);
			QuestNotificationWidget->AddToViewport();
		}
	}
	else if(Notification == EQuestNotification::CompletedQuest)
	{
		QuestCompleteNotifyWidget = CreateWidget<UKerraWidgetBase>(KerraPC, QuestCompleteNotifyWidgetClass);
		if(OnAddQuest.IsBound())
		{
			OnAddQuest.Broadcast(QuestInfo);
			QuestCompleteNotifyWidget->AddToViewport();
		}
	}
}

void UKerraQuestComponent::ClearQuest(FGameplayTag QuestTagToClear)
{
	/*
	 * TODO
	 * receive reward, xp, etc...
	 * notify to widget
	 */
	if(AcceptedQuests.HasTagExact(QuestTagToClear))
	{
		AcceptedQuests.RemoveTag(QuestTagToClear);
		AcceptedQuestsMap.Remove(QuestTagToClear);
		CompletedQuests.AddTag(QuestTagToClear);
		// CompletedQuestsMap.Append(TMap<FGameplayTag, FKerraQuestInfo>(QuestTagToClear, FKerraQuestInfo()))

		UE_LOG(LogTemp, Warning, TEXT("Clear Quest %s"), *QuestTagToClear.ToString());
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
	
	FKerraQuestInfo TargetQuest = AcceptedQuestsMap[TagToCheck];
	for(const auto Pair : TargetQuest.RequireObjects)
	{
		if(InventoryComp->GetCurrentItemCount(Pair.Key) < Pair.Value)
		{
			return false;
		}
	}
	return true;
}


FGameplayTag UKerraQuestComponent::TrackingQuest(FKerraQuestInfo QuestToTrack)
{
	return QuestToTrack.QuestID;
}

void UKerraQuestComponent::ObjectiveUpdate(FKerraQuestInfo TrackedQuest)
{
	UE_LOG(LogTemp, Warning, TEXT("Objective Update Delegate Function"));
}
