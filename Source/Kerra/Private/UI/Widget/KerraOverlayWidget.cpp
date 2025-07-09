// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/KerraOverlayWidget.h"

#include "KerraGameplayTags.h"

void UKerraOverlayWidget::SetParams(AKerraPlayerController* PC, AKerraPlayerState* PS, UKerraAbilitySystemComponent* ASC, UKerraAttributeSet* AS)
{
	KerraPC = PC;
	KerraPS = PS;
	KerraASC = ASC;
	KerraAS = AS;
}

void UKerraOverlayWidget::SetParamsInSubOverlayWidget(UKerraOverlayWidget* TargetOverlayWidget)
{
	TargetOverlayWidget->SetParams(KerraPC, KerraPS, KerraASC, KerraAS);
	
}


