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
	}
	else
	{
		QuestWidget->RemoveFromParent();
		KerraPC->SetShowMouseCursor(false);
		KerraPC->SetInputMode(FInputModeGameOnly());
		QuestWidget = nullptr;
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
		
		TrackQuestWidget = CreateWidget<UKerraWidgetBase>(KerraPC, TrackQuestWidgetClass);
		OnAddQuest.Broadcast(*QuestInfoToAdd);
		TrackQuestWidget->AddToViewport();
		return true;
	}
	return false;
}

void UKerraQuestComponent::AddItemInQuestObjectives(const FGameplayTag ItemIDTag, const FGameplayTagContainer& UsedQuests)
{
	/* 아이템이 적용되는 quest 리스트에서 iter를 돌아 map에서 찾고 object list 추적 */
	/* TODO: 여기에서 바로 퀘스트 완료 검사를 안 하고 퀘스트 완료 버튼 만들고 누를 때 검사하도록 변경하기
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

			//CanCompleteQuest(AcceptedQuestsMap[QuestTag], AcceptedQuestsMap[QuestTag].QuestClearType);
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
	FindQuestID(ItemName, NpcName, Area, IsFound, QuestID, QuestIndex, QuestInfo);

	/*
	 * 1. 오브젝트 카운팅 해주고
	 * 2. quest가 완료되는지 확인하고
	 * 3. 완료할 수 있으면 퀘스트를 accepted에서 complete로 넣어줌
	 */

	/*FQuestObjective CurrentQuestObjective;
	int32 ObjectIndex;
	if(IsFound)
	{
		if(GetCurrentObjective(QuestInfo, CurrentQuestObjective, ObjectIndex))
		{
			if(CurrentQuestObjective.ItemName == ItemName)
			{
				// QuestInfo.Objectives[ObjectIndex].CurrentAmount = ++CurrentQuestObjective.CurrentAmount;
				CurrentQuestObjective.CurrentAmount++;
				QuestInfo.Objectives[ObjectIndex] = CurrentQuestObjective;

				AcceptedQuests[QuestIndex] = QuestInfo;
				OnObjectiveChanged.Broadcast(QuestInfo);

				FKerraQuestInfo CheckedQuest;
				if(CanQuestCompleted(QuestInfo, CheckedQuest))
				{
					CompleteQuest(CheckedQuest);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Add Item To Inventory"));
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Add Item To Inventory"));
	}*/
}

void UKerraQuestComponent::FindQuestID(EQuestItemName ItemName, ENpcName NpcName, EQuestArea Area, bool& OutFound, FGameplayTag& OutQuestID, int32& OutQuestIndex, FKerraQuestInfo& OutQuestInfo)
{
	/* Find quest id in accepted quests */
	
	/*FQuestObjective CurrentObjective;
	int32 CurrentObjectiveIndex = -1;
	
	if(ItemName != EQuestItemName::None)
	{
		bool FoundQuestID = false;
		for(FKerraQuestInfo& QuestInfo : AcceptedQuests)
		{
			if(GetCurrentObjective(QuestInfo, CurrentObjective, CurrentObjectiveIndex))
			{
				if(ItemName == CurrentObjective.ItemName)
				{
					FoundQuestID = true;
					break;
				}	
			}
			CurrentObjectiveIndex++;
		}
		if(FoundQuestID)
		{
			OutFound = FoundQuestID;
			OutQuestID = AcceptedQuests[CurrentObjectiveIndex].QuestID;
			OutQuestIndex = CurrentObjectiveIndex;
			OutQuestInfo = AcceptedQuests[CurrentObjectiveIndex];
		}
	}
	else
	{
		if(NpcName != ENpcName::None)
		{
			
		}
		else
		{
			if(Area != EQuestArea::None)
			{
				bool FoundQuestID = false;
				for(FKerraQuestInfo& QuestInfo : AcceptedQuests)
				{
					if(GetCurrentObjective(QuestInfo, CurrentObjective, CurrentObjectiveIndex))
					{
						if(Area == CurrentObjective.AreaLocation)
						{
							FoundQuestID = true;
							break;
						}	
					}
					CurrentObjectiveIndex++;
				}
				if(FoundQuestID)
				{
					OutFound = FoundQuestID;
					OutQuestID = AcceptedQuests[CurrentObjectiveIndex].QuestID;
					OutQuestIndex = CurrentObjectiveIndex;
					OutQuestInfo = AcceptedQuests[CurrentObjectiveIndex];
				}
			}
		}
	}*/
}

bool UKerraQuestComponent::GetCurrentObjective(FKerraQuestInfo QuestInfo, FQuestObjective& OutObjective, int32& OutObjectiveIndex)
{
	/*bool IsFound = false;
	FQuestObjective FoundObjective;
	int32 FoundObjectIndex = 0;
	
	for(const FQuestObjective& QuestObject : QuestInfo.Objectives)
	{
		if(QuestObject.CurrentAmount < QuestObject.RequireAmount)
		{
			FoundObjective = QuestObject;
			IsFound = true;
			break;
		}
		FoundObjectIndex++;
	}

	if(IsFound)
	{
		OutObjective = FoundObjective;
		OutObjectiveIndex = FoundObjectIndex;
		return true;	
	}*/

	return false;
}

FKerraQuestInfo UKerraQuestComponent::GetQuestInfoFromQuestName(const FName QuestName, bool& OutIsFound)
{
	/*check(QuestDataTable)

	for(const FName RowName : QuestDataTable->GetRowNames())
	{
		FKerraQuestInfo* QuestInfo = QuestDataTable->FindRow<FKerraQuestInfo>(RowName, "");
		// FName(UEnum::GetValueAsString(QuestInfo->QuestID));
		if(QuestName == UEnum::GetValueAsName(QuestInfo->QuestID))
		{
			OutIsFound = true;
			return *QuestInfo;
		}
	}
	OutIsFound = false;*/
	return FKerraQuestInfo();
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

bool UKerraQuestComponent::CanQuestCompleted(const FKerraQuestInfo& QuestToCheck, FKerraQuestInfo& OutCheckedQuest)
{
	/*for(const FQuestObjective CheckObjective : QuestToCheck.Objectives)
	{
		if(CheckObjective.CurrentAmount < CheckObjective.RequireAmount)
		{
			OutCheckedQuest = QuestToCheck;
			return false;
		}
	}
	OutCheckedQuest = QuestToCheck;*/
	return true;
}

void UKerraQuestComponent::CompleteQuest(FKerraQuestInfo QuestToComplete)
{
	/*bool FoundQuest = false;
	for(const FKerraQuestInfo AcceptedQuest : AcceptedQuests)
	{
		if(AcceptedQuest.QuestID == QuestToComplete.QuestID)
		{
			CompletedQuestNames.Add(UEnum::GetValueAsName(QuestToComplete.QuestID));
			AcceptedQuests.Remove(QuestToComplete);
			FoundQuest = true;
			break;
		}
	}

	if(FoundQuest)
	{
		if(TrackQuestWidget)
		{
			TrackQuestWidget->RemoveFromParent();
			AddQuestNotification(EQuestNotification::CompletedQuest, QuestToComplete);
		}
	}*/
}

FGameplayTag UKerraQuestComponent::TrackingQuest(FKerraQuestInfo QuestToTrack)
{
	return QuestToTrack.QuestID;
}

void UKerraQuestComponent::ObjectiveUpdate(FKerraQuestInfo TrackedQuest)
{
	UE_LOG(LogTemp, Warning, TEXT("Objective Update Delegate Function"));
}
