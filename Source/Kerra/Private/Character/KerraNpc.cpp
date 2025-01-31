// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KerraNpc.h"

#include "KerraGameplayTags.h"
#include "Character/KerraHero.h"
#include "Component/Quest/KerraQuestComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/KerraPlayerController.h"
#include "UI/HUD/KerraHUD.h"
#include "UI/Widget/KerraDialogueWidget.h"
#include "UI/Widget/KerraOverlayWidget.h"


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
	/* TODO: 
	 * Separate npc type (give quest, sell item and etc...)
	 * Add sequence animation
	 */
	UE_LOG(LogTemp, Warning, TEXT("DoInteraction"));
	if(!bHasQuest)
	{
		UE_LOG(LogTemp, Warning, TEXT("This NPC don't has any quest"));
		return;
	}

	FGameplayTag FoundQuestTag = FindQuestTagToGive(TargetActor);
	if(!FoundQuestTag.IsValid())
	{
		return;
	}
	
	if(const UDataTable* QuestTable = QuestComponent->GetQuestDataTable())
	{
		const FKerraQuestInfo* GivingQuest = QuestTable->FindRow<FKerraQuestInfo>(FoundQuestTag.GetTagName(), "");
		TalkDialogue(TargetActor, *GivingQuest);
	}
	//GiveQuestToPlayer(TargetActor);
}


void AKerraNpc::BeginPlay()
{
	Super::BeginPlay();
	InitForQuest();
}

void AKerraNpc::TalkDialogue(AActor* TargetActor, FKerraQuestInfo QuestInfo)
{
	if(AKerraPlayerController* KerraPC = Cast<AKerraPlayerController>(UGameplayStatics::GetPlayerController(TargetActor, 0)))
	{
		if(AKerraHUD* KerraHUD = Cast<AKerraHUD>(KerraPC->GetHUD()))
		{
			KerraHUD->GetDialogueWidget()->SetQuestInfo(this, TargetActor, QuestInfo);
			KerraHUD->GetOverlayWidget()->AddDialogueWindow();
		}
	}
}

FGameplayTag AKerraNpc::FindQuestTagToGive(AActor* TargetActor)
{
	if(IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(TargetActor))
	{
		UKerraQuestComponent* TargetQuestComponent = QuestInterface->GetKerraQuestComponent();
		FGameplayTagContainer TargetAcceptedQuests = TargetQuestComponent->GetAcceptedQuestTags();
		FGameplayTagContainer TargetCompletedQuests = TargetQuestComponent->GetCompletedQuestTags();

		for(const FGameplayTag QuestTag : OwnedQuestTags)
		{
			if(CanGivingQuest(QuestTag, TargetAcceptedQuests, TargetCompletedQuests))
			{
				return QuestTag;
			}
		}
	}
	return FGameplayTag();
}

void AKerraNpc::GiveQuestToPlayer(AActor* TargetActor, FGameplayTag QuestTag)
{
	// TODO: check whether player can get a quest or not
	// IKerraQuestInterface::Execute_DoInteraction(this, TargetActor);

	if(IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(TargetActor))
	{
		UKerraQuestComponent* TargetQuestComponent = QuestInterface->GetKerraQuestComponent();
		checkf(TargetQuestComponent, TEXT("Invalid %s's quest component"), *TargetActor->GetName());

		TargetQuestComponent->AddQuest(QuestTag);
		UE_LOG(LogTemp, Warning, TEXT("Success giving %s quest to player"), *QuestTag.ToString());
	}
	
}

bool AKerraNpc::CanGivingQuest(FGameplayTag TagToGive, FGameplayTagContainer& TargetAcceptedQuests, FGameplayTagContainer& TargetCompletedQuest)
{
	// check already accept quest
	if(TargetAcceptedQuests.HasTagExact(TagToGive))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player character already has %s quest."), *TagToGive.ToString());
		return false;
	}

	// check already clear quest
	if(TargetCompletedQuest.HasTagExact(TagToGive))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player character already complete %s quest"), *TagToGive.ToString());
		return false;
	}

	// check - clear previous quest or not
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
