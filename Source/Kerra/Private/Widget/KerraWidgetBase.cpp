// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/KerraWidgetBase.h"
#include "Interface/KerraUIInterface.h"

void UKerraWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if(IKerraUIInterface* UIInterface = Cast<IKerraUIInterface>(OwningEnemyActor))
	{
		UKerraEnemyUIComponent* EnemyUIComponent = UIInterface->GetEnemyUIComponent();
		checkf(EnemyUIComponent, TEXT("not found enemy ui component from %d"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}

void UKerraWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(IKerraUIInterface* UIInterface = Cast<IKerraUIInterface>(GetOwningPlayerPawn()))
	{
		if(UKerraPlayerUIComponent* PlayerUIComponent = UIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}
