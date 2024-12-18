// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Quest/KerraQuestComponent.h"

#include "KerraGameplayTags.h"
#include "Blueprint/UserWidget.h"
#include "Player/KerraPlayerController.h"
#include "Widget/KerraWidgetBase.h"

void UKerraQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	KerraPC = GetOwningController<AKerraPlayerController>();
	OnObjectiveChanged.AddDynamic(this, &UKerraQuestComponent::ObjectiveUpdate);
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
	/*
	if(!AcceptedQuests.HasTagExact(QuestIDTagToAdd) && !CompletedQuests.HasTagExact(QuestIDTagToAdd))
	{
		// UE_LOG(LogTemp, Warning, TEXT("%s"), *QuestIDTagToAdd.ToString());
		FKerraQuestInfo* QuestInfoToAdd = QuestDataTable->FindRow<FKerraQuestInfo>(QuestIDTagToAdd.GetTagName(), "");
		check(QuestInfoToAdd)
		
		AcceptedQuests.AddTag(QuestIDTagToAdd);
		AcceptedQuestsMap.Add(QuestIDTagToAdd, *QuestInfoToAdd);

		ActiveQuest = *QuestInfoToAdd;
		AddQuestNotification(EQuestNotification::NewQuest, *QuestInfoToAdd);

		return true;
	}
	return false;
	*/
}

void UKerraQuestComponent::AddInQuestObjects(const FGameplayTag ObjectTag, const FGameplayTagContainer& UsedQuests)
{
	/* 아이템이 적용되는 quest 리스트에서 iter를 돌아 map에서 찾고 object list 추적
	 * 여기서 말하는 object는 item, enemy, npc, area(location) 모두
	 * TODO: 여기에서 바로 퀘스트 완료 검사를 안 하고 퀘스트 완료 버튼 만들고 누를 때 검사하도록 변경하기 또는 인벤토리에 아이템 넣어질 때 검사
	 * 누를 때 검사?
	*/

	if(ObjectTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Item.ID"))))
	{
		// If object is item
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ObjectTag.ToString());
		for(FGameplayTag QuestTag : UsedQuests.GetGameplayTagArray())
		{
			const FKerraQuestInfo* QuestInfo = AcceptedQuestsMap.Find(QuestTag);
			if(QuestInfo && QuestInfo->RequireObjects.Contains(ObjectTag))
			{
				AcceptedQuestsMap[QuestTag].RequireObjects[ObjectTag].CurrentAmount++;
				OnObjectiveChanged.Broadcast(AcceptedQuestsMap[QuestTag]);
			}
		}
	}
	else if(ObjectTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("NPC.ID"))))
	{
		// If object is npc
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ObjectTag.ToString());
		OnNotifyCompleteQuest.Broadcast(FKerraQuestInfo());
		/* TODO
		 * NPC 만나는 것은 1번이면 되므로 바로 클리어 되게끔
		 */
	}
	else if(ObjectTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Location.ID"))))
	{
		// If object is location
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ObjectTag.ToString());

		for(FGameplayTag QuestTag : UsedQuests.GetGameplayTagArray())
		{
			
			// Check the is completed required previous quest.
			/*if(!CompletedQuests.HasTagExact(QuestTag))
			{
				const FKerraQuestInfo* QuestInfo = AcceptedQuestsMap.Find(QuestTag);
				if(QuestInfo && QuestInfo->RequireObjects.Contains(ObjectTag))
				{
					AcceptedQuestsMap[QuestTag].RequireObjects[ObjectTag].CurrentAmount++;
					OnObjectiveChanged.Broadcast(AcceptedQuestsMap[QuestTag]);
				}
			}*/
		}
		
		OnNotifyCompleteQuest.Broadcast(FKerraQuestInfo());
		/* TODO
		 * Location 도달하는 것은 1번이면 되므로 바로 클리어 되게끔
		 */
	}

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


FGameplayTag UKerraQuestComponent::TrackingQuest(FKerraQuestInfo QuestToTrack)
{
	return QuestToTrack.QuestID;
}

void UKerraQuestComponent::ObjectiveUpdate(FKerraQuestInfo TrackedQuest)
{
	UE_LOG(LogTemp, Warning, TEXT("Objective Update Delegate Function"));
}
