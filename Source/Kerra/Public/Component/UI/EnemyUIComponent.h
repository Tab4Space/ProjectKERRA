// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/KerraUIComponent.h"
#include "EnemyUIComponent.generated.h"


class UKerraWidgetBase;

UCLASS()
class KERRA_API UEnemyUIComponent : public UKerraUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UKerraWidgetBase* InWidgetToResister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetIfAny();
	

private:
	TArray<UKerraWidgetBase*> EnemyDrawnWidgets;
};
