// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Quest/KerraQuestComponent.h"

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

bool UKerraQuestComponent::AddQuest(FKerraQuestInfo AddQuestInfo)
{
	if(CanAcceptQuest(AddQuestInfo))
	{
		AcceptedQuests.Add(AddQuestInfo);
		ActiveQuest = AddQuestInfo;
		AddQuestNotification(EQuestNotification::NewQuest, AddQuestInfo);

		TrackQuestWidget = CreateWidget<UKerraWidgetBase>(KerraPC, TrackQuestWidgetClass);
		OnAddQuest.Broadcast(AddQuestInfo);
		TrackQuestWidget->AddToViewport();
		return true;
	}
	return false;
}

bool UKerraQuestComponent::CanAcceptQuest(FKerraQuestInfo CheckQuestInfo)
{
	/* Check accept quest or not */
	if(CheckCompletedQuest(CheckQuestInfo))
		return false;

	bool bIsFound = true;
	for(const FKerraQuestInfo Info : AcceptedQuests)
	{
		if(Info.QuestID == CheckQuestInfo.QuestID)
		{
			bIsFound = false;
			break;
		}
	}
	return bIsFound;
}

bool UKerraQuestComponent::CheckCompletedQuest(FKerraQuestInfo CheckQuestInfo)
{
	/* Check already completed quest or not*/
	bool bIsFound = false;
	
	for(FName QuestName : CompletedQuestNames)
	{
		if(bIsFound)
		{
			break;
		}

		const FName DisplayName = FName(UEnum::GetDisplayValueAsText(CheckQuestInfo.QuestID).ToString());
		if(QuestName == DisplayName)
		{
			bIsFound = true;
		}
	}

	if(bIsFound)
	{
		if(CheckQuestInfo.bRepeatable)
		{
			return true;
		}
	}
	return false;
}

void UKerraQuestComponent::AddItemToQuestObjective(EQuestItemName ItemName, ENpcName NpcName, EQuestArea Area)
{
	bool IsFound = false;
	EQuestName QuestID;
	int32 QuestIndex;
	FKerraQuestInfo QuestInfo;
	FindQuestID(ItemName, NpcName, Area, IsFound, QuestID, QuestIndex, QuestInfo);

	FQuestObjective CurrentQuestObjective;
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
	}
}

void UKerraQuestComponent::FindQuestID(EQuestItemName ItemName, ENpcName NpcName, EQuestArea Area, bool& OutFound, EQuestName& OutQuestName, int32& OutQuestIndex, FKerraQuestInfo& OutQuestInfo)
{
	/* Find quest id in accepted quests */
	FQuestObjective CurrentObjective;
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
			OutQuestName = AcceptedQuests[CurrentObjectiveIndex].QuestID;
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
					OutQuestName = AcceptedQuests[CurrentObjectiveIndex].QuestID;
					OutQuestIndex = CurrentObjectiveIndex;
					OutQuestInfo = AcceptedQuests[CurrentObjectiveIndex];
				}
			}
		}
	}
}

bool UKerraQuestComponent::GetCurrentObjective(FKerraQuestInfo QuestInfo, FQuestObjective& OutObjective, int32& OutObjectiveIndex)
{
	bool IsFound = false;
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
	}

	return false;
}

FKerraQuestInfo UKerraQuestComponent::GetQuestInfoFromQuestName(const FName QuestName, bool& OutIsFound)
{
	check(QuestDataTable)

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
	OutIsFound = false;
	return FKerraQuestInfo();
}

void UKerraQuestComponent::AddQuestNotification(EQuestNotification Notification, FKerraQuestInfo& QuestInfo)
{
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
	for(const FQuestObjective CheckObjective : QuestToCheck.Objectives)
	{
		if(CheckObjective.CurrentAmount < CheckObjective.RequireAmount)
		{
			OutCheckedQuest = QuestToCheck;
			return false;
		}
	}
	OutCheckedQuest = QuestToCheck;
	return true;
}

void UKerraQuestComponent::CompleteQuest(FKerraQuestInfo QuestToComplete)
{
	bool FoundQuest = false;
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
	}
}

EQuestName UKerraQuestComponent::TrackingQuest(FKerraQuestInfo QuestToTrack)
{
	return QuestToTrack.QuestID;
}

void UKerraQuestComponent::ObjectiveUpdate(FKerraQuestInfo TrackedQuest)
{
	UE_LOG(LogTemp, Warning, TEXT("Objective Update Delegate Function"));
}
