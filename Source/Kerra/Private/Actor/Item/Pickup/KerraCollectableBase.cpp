// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Pickup/KerraCollectableBase.h"

#include "Component/Inventory/KerraInventoryComponent.h"
#include "Interface/KerraInventoryInterface.h"

AKerraCollectableBase::AKerraCollectableBase()
{
}

void AKerraCollectableBase::DoInteraction_Implementation(AActor* TargetActor)
{
	if(IKerraInventoryInterface* InventoryInterface = Cast<IKerraInventoryInterface>(TargetActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Target actor name is %s"), *TargetActor->GetActorNameOrLabel());
		UKerraInventoryComponent* TargetInventoryComp = InventoryInterface->GetKerraInventoryComponent();

		if(TargetInventoryComp && TargetInventoryComp->AddItem(ItemIDTag))
		{
			UE_LOG(LogTemp, Warning, TEXT("Add %s in inventory"), *ItemIDTag.ToString());
		}
	}
}
