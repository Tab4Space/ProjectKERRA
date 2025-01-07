// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/KerraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/KerraWidgetBase.h"

void AKerraHUD::InitMainOverlayWidget()
{
	checkf(MainOverlayWidgetClass, TEXT("Main Overlay Widget Class Uninitialized, please fill out BP_KerraHUD"));
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainOverlayWidgetClass);
	MainOverlayWidget = Cast<UKerraWidgetBase>(Widget);
	Widget->AddToViewport();
}
