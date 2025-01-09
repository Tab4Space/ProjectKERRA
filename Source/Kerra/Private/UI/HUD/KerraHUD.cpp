// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/KerraHUD.h"

#include "Blueprint/UserWidget.h"
#include "Player/KerraPlayerController.h"
#include "UI/Widget/KerraOverlayWidget.h"
#include "UI/Widget/KerraQuestWidget.h"

void AKerraHUD::InitMainOverlayWidget()
{
	checkf(MainOverlayWidgetClass, TEXT("Main Overlay Widget Class Uninitialized, please fill out BP_KerraHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainOverlayWidgetClass);
	MainOverlayWidget = Cast<UKerraOverlayWidget>(Widget);
	Widget->AddToViewport();
}

void AKerraHUD::CreateQuestWidget()
{
	checkf(QuestWidgetClass, TEXT("Quest Widget Class Uninitialized, please fill out BP_KerraHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), QuestWidgetClass);
	QuestWidget = Cast<UKerraQuestWidget>(Widget);
	Widget->AddToViewport();
	
	AKerraPlayerController* KerraPC = Cast<AKerraPlayerController>(GetOwningPlayerController());
	KerraPC->SetShowMouseCursor(true);
	KerraPC->SetInputMode(FInputModeGameAndUI());
}
