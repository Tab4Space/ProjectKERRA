// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/KerraHUD.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/KerraPlayerController.h"
#include "UI/Widget/KerraOverlayWidget.h"
#include "UI/Widget/KerraQuestWidget.h"
#include "UI/Widget/KerraDialogueWidget.h"
#include "UI/Widget/KerraInventoryWidget.h"


void AKerraHUD::InitMainOverlayWidget()
{
	checkf(MainOverlayWidgetClass, TEXT("Main Overlay Widget Class Uninitialized, please fill out BP_KerraHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MainOverlayWidgetClass);
	MainOverlayWidget = Cast<UKerraOverlayWidget>(Widget);
	Widget->AddToViewport();
}

void AKerraHUD::CreateQuestWidget()
{
	checkf(QuestWidgetClass, TEXT("Quest Widget Class Uninitialized, please fill out BP_KerraHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), QuestWidgetClass);
	QuestWidget = Cast<UKerraQuestWidget>(Widget);
}

void AKerraHUD::CreateDialogueWidget()
{
	checkf(QuestWidgetClass, TEXT("Dialogue Widget Class Uninitialized, please fill out BP_KerraHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), DialogueWidgetClass);
	DialogueWidget = Cast<UKerraDialogueWidget>(Widget);
}

void AKerraHUD::CreateInventoryWidget()
{
	checkf(InventoryWidgetClass, TEXT("Dialogue Widget Class Uninitialized, please fill out BP_KerraHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), InventoryWidgetClass);
	InventoryWidget = Cast<UKerraInventoryWidget>(Widget);
}

void AKerraHUD::SetPlayerOverlayWidget(UKerraOverlayWidget* InPlayerOverlayWidget)
{
	PlayerOverlayWidget = InPlayerOverlayWidget;
}

