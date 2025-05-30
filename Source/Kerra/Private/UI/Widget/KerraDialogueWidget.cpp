// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/KerraDialogueWidget.h"

#include "Character/KerraHero.h"
#include "Character/KerraNpc.h"

void UKerraDialogueWidget::SetQuestInfo(AActor* InNpcActor, AActor* InPlayerActor, FKerraQuestData InQuestInfo)
{
	NpcActor = Cast<AKerraNpc>(InNpcActor);
	PlayerActor = Cast<AKerraHero>(InPlayerActor);
	QuestInfo = InQuestInfo;

	
}
