// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KerraNpc.h"

#include "KerraGameplayTags.h"
#include "Component/Quest/KerraQuestComponent.h"


AKerraNpc::AKerraNpc()
{
	QuestComponent = CreateDefaultSubobject<UKerraQuestComponent>("QuestComponent");
}

void AKerraNpc::InitForQuest()
{
	if(QuestComponent == nullptr || OwnedQuestTags.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("This NPC does not have a quest or quest component."));
		return;
	}

	if(const UDataTable* QuestDataTable = QuestComponent->GetQuestDataTable())
	{
		for(FGameplayTag QuestTag : OwnedQuestTags.GetGameplayTagArray())
		{
			if(const FKerraQuestInfo* QuestInfoToAdd = QuestDataTable->FindRow<FKerraQuestInfo>(QuestTag.GetTagName(), ""))
			{
				OwnedQuests.Add(*QuestInfoToAdd);
			}
		}

		if(!OwnedQuests.IsEmpty())
		{
			bHasQuest = true;
		}
	}
}

void AKerraNpc::DoInteraction_Implementation(AActor* TargetActor)
{
	UE_LOG(LogTemp, Warning, TEXT("DoInteraction"));
	// TODO: adding dialogue.

	if(bHasQuest)
	{
		GiveQuestToPlayer(TargetActor);	
	}
}


void AKerraNpc::BeginPlay()
{
	Super::BeginPlay();
	InitForQuest();
}

void AKerraNpc::GiveQuestToPlayer(AActor* TargetActor)
{
	// TODO: check whether player can get a quest or not
	// IKerraQuestInterface::Execute_DoInteraction(this, TargetActor);
	if(IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(TargetActor))
	{
		UKerraQuestComponent* TargetQuestComponent = QuestInterface->GetQuestComponent();

		for(FKerraQuestInfo& QuestInfo : OwnedQuests)
		{
			if(TargetQuestComponent->AddQuest(QuestInfo.QuestID))
			{
				break;
			}
		}
	}
}
