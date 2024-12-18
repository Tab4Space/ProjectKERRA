// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/KerraCheatManager.h"

#include "Component/Quest/KerraQuestComponent.h"
#include "Interface/KerraQuestInterface.h"
#include "Player/KerraPlayerController.h"

void UKerraCheatManager::Console_ClearQuest(FString QuestTag)
{
	if(AKerraPlayerController* KerraPC = Cast<AKerraPlayerController>(GetPlayerController()))
	{
		IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(KerraPC->GetPawn());
		UKerraQuestComponent* TargetQuestComp = QuestInterface->GetQuestComponent();

		TargetQuestComp->ClearQuest(FGameplayTag::RequestGameplayTag(FName(QuestTag)));
		
		UE_LOG(LogTemp, Warning, TEXT("Execute command (Clear Quest %s)."), *QuestTag);
	}
}
