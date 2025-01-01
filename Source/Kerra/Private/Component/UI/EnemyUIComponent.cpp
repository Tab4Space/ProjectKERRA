// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/EnemyUIComponent.h"
#include "UI/Widget/KerraWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UKerraWidgetBase* InWidgetToResister)
{
	EnemyDrawnWidgets.Add(InWidgetToResister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetIfAny()
{
	if(EnemyDrawnWidgets.IsEmpty())
	{
		return;
	}
	for(UKerraWidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if(DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}
	EnemyDrawnWidgets.Empty();
}
