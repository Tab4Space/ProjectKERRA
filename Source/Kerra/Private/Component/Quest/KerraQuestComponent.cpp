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
	 * TODO: check repeatable quest
	 */
	
	if(!AcceptedQuests.HasTagExact(QuestIDTagToAdd) && !CompletedQuests.HasTagExact(QuestIDTagToAdd))
	{
		FKerraQuestInfo* QuestInfoToAdd = QuestDataTable->FindRow<FKerraQuestInfo>(QuestIDTagToAdd.GetTagName(), "");
		check(QuestInfoToAdd)
		AcceptedQuests.AddTag(QuestIDTagToAdd);
		AcceptedQuestsMap.Add(QuestIDTagToAdd, *QuestInfoToAdd);

		ActiveQuest = *QuestInfoToAdd;
		AddQuestNotification(EQuestNotification::NewQuest, *QuestInfoToAdd);

		return true;
	}
	return false;
}

void UKerraQuestComponent::AddItemInQuestObjectives(const FGameplayTag ItemIDTag, const FGameplayTagContainer& UsedQuests)
{
	/* 아이템이 적용되는 quest 리스트에서 iter를 돌아 map에서 찾고 object list 추적 */
	/* TODO: 여기에서 바로 퀘스트 완료 검사를 안 하고 퀘스트 완료 버튼 만들고 누를 때 검사하도록 변경하기 또는 인벤토리에 아이템 넣어질 때 검사
	 * 누를 때
	*/
	for(FGameplayTag QuestTag : UsedQuests.GetGameplayTagArray())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *QuestTag.ToString())
		const FKerraQuestInfo* QuestInfo = AcceptedQuestsMap.Find(QuestTag);

		if(QuestInfo && QuestInfo->RequireObjects.Contains(ItemIDTag))
		{
			AcceptedQuestsMap[QuestTag].RequireObjects[ItemIDTag].CurrentAmount++;
			OnObjectiveChanged.Broadcast(AcceptedQuestsMap[QuestTag]);
		}
	}
}

void UKerraQuestComponent::CanCompleteQuest(const FKerraQuestInfo QuestInfo, const EQuestClearType ClearType)
{
	if(ClearType == EQuestClearType::CollectItem)
	{
		// if(QuestInfo.RequireObjects)
	}
}

void UKerraQuestComponent::AddItemToQuestObjective(EQuestItemName ItemName, ENpcName NpcName, EQuestArea Area)
{
	bool IsFound = false;
	FGameplayTag QuestID;
	int32 QuestIndex;
	FKerraQuestInfo QuestInfo;
	// FindQuestID(ItemName, NpcName, Area, IsFound, QuestID, QuestIndex, QuestInfo);
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


FGameplayTag UKerraQuestComponent::TrackingQuest(FKerraQuestInfo QuestToTrack)
{
	return QuestToTrack.QuestID;
}

void UKerraQuestComponent::ObjectiveUpdate(FKerraQuestInfo TrackedQuest)
{
	UE_LOG(LogTemp, Warning, TEXT("Objective Update Delegate Function"));
}
