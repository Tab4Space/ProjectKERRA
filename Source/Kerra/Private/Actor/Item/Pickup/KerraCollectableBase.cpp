// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Pickup/KerraCollectableBase.h"

#include "Component/Quest/KerraQuestComponent.h"

AKerraCollectableBase::AKerraCollectableBase()
{
}

void AKerraCollectableBase::DoInteraction_Implementation(AActor* TargetActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetActor->GetActorNameOrLabel());

	if(!bUseInQuest || AppliedQuests.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("This item is not for quest or not in used quest"));
		return;
	}
	
	if(IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(TargetActor))
	{
		UKerraQuestComponent* TargetQuestComponent = QuestInterface->GetQuestComponent();
		TargetQuestComponent->AddInQuestObjects(ItemIDTag, AppliedQuests);
		/*
		 * TODO
		 * 지금은 quest에 바로 추가하는데 inventory 만들면 inventory에 추가하고 inventory에서 widget에 알려주는 로직으로
		 * 
		 */
	}
	
}
