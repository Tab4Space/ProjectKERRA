// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/KerraOverlayWidget.h"

#include "KerraGameplayTags.h"

void UKerraOverlayWidget::SetParams(AKerraPlayerController* PC, AKerraPlayerState* PS, UKerraAbilitySystemComponent* ASC, UKerraAttributeSet* AS)
{
	KerraPC = PC;
	KerraPS = PS;
	KerraASC = ASC;
	KerraAS = AS;

	for(auto a : KerraASC->GetActivatableAbilities())
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"));
	}
	
	
	
}
