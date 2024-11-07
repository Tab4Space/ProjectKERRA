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
