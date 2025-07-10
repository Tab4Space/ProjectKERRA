// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Overlay/KerraOverlayWidget.h"

#include "KerraGameplayTags.h"

void UKerraOverlayWidget::SetParams(AKerraPlayerController* PC, AKerraPlayerState* PS, UKerraAbilitySystemComponent* ASC, UKerraAttributeSet* AS)
{
	/* run on main overlay widget */
	KerraPC = PC;
	KerraPS = PS;
	KerraASC = ASC;
	KerraAS = AS;
}

void UKerraOverlayWidget::BindEvents()
{
}


