// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/KerraHUD.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/KerraPlayerController.h"
#include "UI/Widget/Overlay/KerraOverlayWidget.h"
#include "UI/Widget/KerraQuestWidget.h"
#include "UI/Widget/KerraDialogueWidget.h"
#include "UI/Widget/KerraInventoryWidget.h"


void AKerraHUD::InitMainOverlayWidget(AKerraPlayerController* PC, AKerraPlayerState* PS, UKerraAbilitySystemComponent* ASC, UKerraAttributeSet* AS)
{
	checkf(MainOverlayWidgetClass, TEXT("Main Overlay Widget Class Uninitialized, please fill out BP_KerraHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MainOverlayWidgetClass);
	MainOverlayWidget = Cast<UKerraOverlayWidget>(Widget);
	
	KerraPC = PC;
	KerraPS = PS;
	KerraASC = ASC;
	KerraAS = AS;
	
	MainOverlayWidget->SetParams(PC, PS, ASC, AS);
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

void AKerraHUD::SetInventoryOverlayWidget(UKerraOverlayWidget* InInventoryOverlayWidget)
{
	InventoryOverlayWidget = InInventoryOverlayWidget;
}

void AKerraHUD::SetQuestOverlayWidget(UKerraOverlayWidget* InQuestOverlayWidget)
{
	QuestOverlayWidget = InQuestOverlayWidget;
}

void AKerraHUD::SetSkillOverlayWidget(UKerraOverlayWidget* InSkillOverlayWidget)
{
	SkillOverlayWidget = InSkillOverlayWidget;
}

void AKerraHUD::SetWorldMapOverlayWidget(UKerraOverlayWidget* InWorldMapOverlayWidget)
{
	WorldMapOverlayWidget = InWorldMapOverlayWidget;
}

