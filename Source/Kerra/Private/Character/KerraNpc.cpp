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
	if(!bHasQuest)
	{
		UE_LOG(LogTemp, Warning, TEXT("This NPC don't has any quest"));
		return;
	}
	GiveQuestToPlayer(TargetActor);	
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
		FGameplayTagContainer TargetAcceptedQuests = TargetQuestComponent->GetAcceptedQuestTags();
		FGameplayTagContainer TargetCompletedQuests = TargetQuestComponent->GetCompletedQuestTags();

		bool bGiveQuest = false;
		for(const FGameplayTag QuestTag : OwnedQuestTags)
		{
			if(CanGivingQuest(QuestTag, TargetAcceptedQuests, TargetCompletedQuests))
			{
				bGiveQuest = TargetQuestComponent->AddQuest(QuestTag);
				break;
			}
		}

		if(bGiveQuest)
		{
			UE_LOG(LogTemp, Warning, TEXT("Success giving quest to player"));
		}
	}
}

bool AKerraNpc::CanGivingQuest(FGameplayTag TagToGive, FGameplayTagContainer& TargetAcceptedQuests, FGameplayTagContainer& TargetCompletedQuest)
{
	if(TargetAcceptedQuests.HasTagExact(TagToGive))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player character already has %s quest."), *TagToGive.ToString());
		return false;
	}

	if(TargetCompletedQuest.HasTagExact(TagToGive))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player character already complete %s quest"), *TagToGive.ToString());
		return false;
	}

	/*
	 * TODO: check exist previous quest and that is completed?
	 */
	if(const UDataTable* QuestTable = QuestComponent->GetQuestDataTable())
	{
		const FKerraQuestInfo* GivingQuest = QuestTable->FindRow<FKerraQuestInfo>(TagToGive.GetTagName(), "");
		if(GivingQuest->PreviousQuestID.IsValid() && !TargetCompletedQuest.HasTagExact(GivingQuest->PreviousQuestID))
		{
			UE_LOG(LogTemp, Warning, TEXT("Player must be clear %s quest"), *GivingQuest->PreviousQuestID.ToString());
			return false;
		}
	}
	return true;
}
