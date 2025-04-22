// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/KerraInventoryWidget.h"

#include "Player/KerraPlayerController.h"

void UKerraInventoryWidget::ToggleShowingWindow()
{
	AKerraPlayerController* KerraPC = Cast<AKerraPlayerController>(GetOwningPlayer());
	if(GetVisibility() == ESlateVisibility::Hidden)
	{
		SetVisibility(ESlateVisibility::Visible);
		SetUIMode(true);
		
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
		SetUIMode(false);
	}
}
