// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/KerraCheatManager.h"

#include "Component/Quest/KerraQuestComponent.h"
#include "Interface/KerraQuestInterface.h"
#include "Component/Inventory/KerraInventoryComponent.h"
#include "Interface/KerraInventoryInterface.h"
#include "Player/KerraPlayerController.h"

void UKerraCheatManager::Console_ClearQuest(FString QuestTag)
{
	if(AKerraPlayerController* KerraPC = Cast<AKerraPlayerController>(GetPlayerController()))
	{
		IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(KerraPC->GetPawn());
		UKerraQuestComponent* TargetQuestComp = QuestInterface->GetKerraQuestComponent();

		TargetQuestComp->ClearQuest(FGameplayTag::RequestGameplayTag(FName(QuestTag)));
		
		UE_LOG(LogTemp, Warning, TEXT("Execute command (Clear Quest %s)."), *QuestTag);
	}
}

void UKerraCheatManager::Console_AddItem(FString ItemTag, int32 AddCount)
{
	if(AKerraPlayerController* KerraPC = Cast<AKerraPlayerController>(GetPlayerController()))
	{
		IKerraInventoryInterface* InventoryInterface = Cast<IKerraInventoryInterface>(KerraPC->GetPawn());
		UKerraInventoryComponent* TargetInventoryComp = InventoryInterface->GetKerraInventoryComponent();

		if(TargetInventoryComp->AddItem(FGameplayTag::RequestGameplayTag(FName(ItemTag)), AddCount))
		{
			UE_LOG(LogTemp, Warning, TEXT("Execute command (Add Item %s, %dEA)."), *ItemTag, AddCount);
		}
	}
}
