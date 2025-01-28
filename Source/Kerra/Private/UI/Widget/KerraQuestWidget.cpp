// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/KerraQuestWidget.h"

#include "Player/KerraPlayerController.h"

void UKerraQuestWidget::ToggleWindow()
{
	AKerraPlayerController* KerraPC = Cast<AKerraPlayerController>(GetOwningPlayer());
	if(GetVisibility() != ESlateVisibility::Hidden)
	{
		SetVisibility(ESlateVisibility::Hidden);
		SetUIMode(false);
		/*KerraPC->SetShowMouseCursor(false);
		KerraPC->SetInputMode(FInputModeGameOnly());*/
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
		SetUIMode(true);
		/*KerraPC->SetShowMouseCursor(true);
		KerraPC->SetInputMode(FInputModeGameAndUI());*/
	}
}
