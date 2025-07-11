// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/KerraWidgetBase.h"
#include "Interface/KerraInventoryInterface.h"
#include "Interface/KerraQuestInterface.h"
#include "Interface/KerraWidgetInterface.h"
#include "UI/HUD/KerraHUD.h"


void UKerraWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if(IKerraWidgetInterface* UIInterface = Cast<IKerraWidgetInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = UIInterface->GetEnemyUIComponent();
		checkf(EnemyUIComponent, TEXT("not found enemy ui component from %d"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}

void UKerraWidgetBase::ToggleShowingWindow()
{
}

AKerraHUD* UKerraWidgetBase::GetKerraHUD()
{
	return Cast<AKerraHUD>(GetOwningPlayer()->GetHUD());
}

void UKerraWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	// KERRALOG(Warning, TEXT("%s"), *this->GetDisplayLabel());

	if(IKerraWidgetInterface* UIInterface = Cast<IKerraWidgetInterface>(GetOwningPlayerPawn()))
	{
		if(UHeroUIComponent* PlayerUIComponent = UIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(PlayerUIComponent);
		}
	}

	if(IKerraQuestInterface* QuestInterface = Cast<IKerraQuestInterface>(GetOwningPlayerPawn()))
	{
		if(UKerraQuestComponent* QuestComponent = QuestInterface->GetKerraQuestComponent())
		{
			BP_OnOwningPlayerQuestComponentIntialized(QuestComponent);
		}
	}

	if(IKerraInventoryInterface* InventoryInterface = Cast<IKerraInventoryInterface>(GetOwningPlayerPawn()))
	{
		if(UKerraInventoryComponent* InventoryComponent = InventoryInterface->GetKerraInventoryComponent())
		{
			BP_OnOwningInventoryComponentInitialized(InventoryComponent);
		}
		
	}
}

void UKerraWidgetBase::SetUIMode(bool IsShowing)
{
	if(IsShowing)
	{
		GetOwningPlayer()->SetShowMouseCursor(IsShowing);
		GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		GetOwningPlayer()->SetShowMouseCursor(IsShowing);
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	}
}
