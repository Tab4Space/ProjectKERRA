// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Overlay/SkillOverlayWidget.h"

#include "Kerra/Kerra.h"
#include "UI/HUD/KerraHUD.h"

void USkillOverlayWidget::InitSkillOverlay(UKerraOverlayWidget* InParentWidget)
{
	ParentOverlayWidget = InParentWidget;
	
	AKerraPlayerController* PC = ParentOverlayWidget->GetKerraPC();
	AKerraPlayerState* PS = ParentOverlayWidget->GetKerraPS();
	UKerraAbilitySystemComponent* ASC = ParentOverlayWidget->GetKerraASC();
	UKerraAttributeSet* AS = ParentOverlayWidget->GetKerraAS();

	SetParams(PC, PS, ASC, AS);
	BindEvents();
}

void USkillOverlayWidget::BindEvents()
{
	/* skill 쪽에 관련있을 법한 것들 바인딩 */
	GetKerraPS()->OnSkillPointsChanged.AddDynamic(this, &USkillOverlayWidget::OnChangeSkillPoints);
	
}

void USkillOverlayWidget::OnChangeSkillPoints_Implementation(int32 InPoints)
{
	/* parent implementation function */
	
	KERRALOG(Warning, TEXT("%d"), InPoints);
	//OnChangeSkillPoints(InPoints);
}


void USkillOverlayWidget::NativeOnInitialized()
{
	// Super::NativeOnInitialized();
	
}
