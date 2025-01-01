// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/KerraWidgetBase.h"
#include "Interface/KerraInventoryInterface.h"
#include "Interface/KerraQuestInterface.h"
#include "Interface/KerraWidgetInterface.h"


void UKerraWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if(IKerraWidgetInterface* UIInterface = Cast<IKerraWidgetInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = UIInterface->GetEnemyUIComponent();
		checkf(EnemyUIComponent, TEXT("not found enemy ui component from %d"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}

void UKerraWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

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
