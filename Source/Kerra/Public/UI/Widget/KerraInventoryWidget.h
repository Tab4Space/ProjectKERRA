// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/KerraWidgetBase.h"
#include "KerraInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class KERRA_API UKerraInventoryWidget : public UKerraWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ToggleWidget();
};
