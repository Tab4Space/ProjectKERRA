// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KerraNpc.h"

#include "KerraFunctionLibrary.h"
#include "KerraGameplayTags.h"
#include "Character/KerraHero.h"
#include "Component/Quest/KerraQuestComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/KerraPlayerController.h"
#include "Struct/KerraItemInfo.h"
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

	for(FGameplayTag QuestTag : OwnedQuestTags.GetGameplayTagArray())
	{
		FKerraQuestInfo QuestInfo = UKerraFunctionLibrary::GetQuestInfoByTagFromKerraGI(QuestTag, this);
		OwnedQuests.AddUnique(QuestInfo);
	}

	if(!OwnedQuests.IsEmpty())
	{
		bHasQuest = true;
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

	const FGameplayTag FoundQuestTag = FindQuestTagToGive(TargetActor);
	if(!FoundQuestTag.IsValid())
	{
		return;
	}

	AKerraHUD* KerraHUD = UKerraFunctionLibrary::NativeGetKerraHUD(Cast<AKerraHero>(TargetActor)->GetKerraPC());
	KerraHUD->CreateDialogueWidget();

	const FKerraQuestInfo QuestToGive = UKerraFunctionLibrary::GetQuestInfoByTagFromKerraGI(FoundQuestTag, this);
	if(QuestToGive.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *QuestToGive.QuestID.ToString());
		TalkDialogue(TargetActor, QuestToGive);
	}

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
	if(const IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(TargetActor))
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

	if(const IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(TargetActor))
	{
		UKerraQuestComponent* TargetQuestComponent = QuestInterface->GetKerraQuestComponent();
		checkf(TargetQuestComponent, TEXT("Invalid %s's quest component"), *TargetActor->GetName());

		TargetQuestComponent->AddQuest(QuestTag);
		UE_LOG(LogTemp, Warning, TEXT("Success giving %s quest to player"), *QuestTag.ToString());
	}
	
}

bool AKerraNpc::CanGivingQuest(FGameplayTag TagToGive, FGameplayTagContainer& TargetAcceptedQuests, FGameplayTagContainer& TargetCompletedQuest)
{
	// check player already accept quest or not
	if(TargetAcceptedQuests.HasTagExact(TagToGive))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player character already has %s quest."), *TagToGive.ToString());
		return false;
	}

	// check player already clear quest or not
	if(TargetCompletedQuest.HasTagExact(TagToGive))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player character already complete %s quest"), *TagToGive.ToString());
		return false;
	}

	// check player clear required quest or not
	const FKerraQuestInfo FoundQuest = UKerraFunctionLibrary::GetQuestInfoByTagFromKerraGI(TagToGive, this);
	if(FoundQuest.PreviousQuestID.IsValid() && !TargetCompletedQuest.HasTagExact(FoundQuest.PreviousQuestID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player must be clear %s quest"), *FoundQuest.PreviousQuestID.ToString());
		return false;
	}
	return true;
}
