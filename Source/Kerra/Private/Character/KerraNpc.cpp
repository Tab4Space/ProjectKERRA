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
	if(!bHasQuest)
	{
		return;
	}
	
	UDataTable* QuestDataTable = QuestComponent->GetQuestDataTable();

	check(QuestDataTable)
	for(const FName RowName : QuestDataTable->GetRowNames())
	{
		FKerraQuestInfo* QuestInfo = QuestDataTable->FindRow<FKerraQuestInfo>(RowName, "");
		if(NpcName == QuestInfo->QuestGiver)
		{
			OwnedQuest.Add(*QuestInfo);
		}
	}
}

void AKerraNpc::DoInteraction_Implementation(AActor* TargetActor)
{
	UE_LOG(LogTemp, Warning, TEXT("DoInteraction"));
	GiveQuestToPlayer(TargetActor);
}


void AKerraNpc::BeginPlay()
{
	Super::BeginPlay();
	InitForQuest();
}

void AKerraNpc::GiveQuestToPlayer(AActor* TargetActor)
{
	// IKerraQuestInterface::Execute_DoInteraction(this, TargetActor);
	if(IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(TargetActor))
	{
		UKerraQuestComponent* TargetQuestComponent = QuestInterface->GetQuestComponent();

		for(FKerraQuestInfo& QuestInfo : OwnedQuest)
		{
			bool bSuccessGiving = TargetQuestComponent->AddQuest(KerraGameplayTags::Quest_ID_FirstQuest);
			if(bSuccessGiving)
			{
				break;
			}
		}
	}

}
