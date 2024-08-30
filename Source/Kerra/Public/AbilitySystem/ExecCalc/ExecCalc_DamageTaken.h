// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_DamageTaken.generated.h"

/**
 * 
 */
UCLASS()
class KERRA_API UExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecCalc_DamageTaken();

	// Called whenever the owning gameplay effect is executed. Allowed to do essentially whatever is desired, including generating new modifiers to instantly execute as well.
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
