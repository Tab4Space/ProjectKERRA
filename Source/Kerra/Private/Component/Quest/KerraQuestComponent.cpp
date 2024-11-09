// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Quest/KerraQuestComponent.h"

#include "Blueprint/UserWidget.h"
#include "Player/KerraPlayerController.h"
#include "Widget/KerraWidgetBase.h"

void UKerraQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	
	KerraPC = GetOwningController<AKerraPlayerController>();
	
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
	
	for(FName QuestName : CompletedQuest)
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
