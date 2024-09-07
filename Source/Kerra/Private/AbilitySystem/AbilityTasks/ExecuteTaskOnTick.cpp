// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/ExecuteTaskOnTick.h"

UExecuteTaskOnTick::UExecuteTaskOnTick()
{
	bTickingTask = true;
}

UExecuteTaskOnTick* UExecuteTaskOnTick::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
	UExecuteTaskOnTick* Node = NewAbilityTask<UExecuteTaskOnTick>(OwningAbility);
	return Node;
}

void UExecuteTaskOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTaskTick.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}
