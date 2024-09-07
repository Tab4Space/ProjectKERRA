// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ExecuteTaskOnTick.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickDelegate, float, DeltaTime);

UCLASS()
class KERRA_API UExecuteTaskOnTick : public UAbilityTask
{
	GENERATED_BODY()

public:
	UExecuteTaskOnTick();
	
	UFUNCTION(BlueprintCallable, Category="Kerra|AbilityTasks", meta=(HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly="true"))
	static UExecuteTaskOnTick* ExecuteTaskOnTick(UGameplayAbility* OwningAbility); 

	/* Interface */
	virtual void TickTask(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskTickDelegate OnAbilityTaskTick;
};
