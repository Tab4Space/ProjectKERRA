// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/KerraWidgetBase.h"
#include "KerraOverlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class KERRA_API UKerraOverlayWidget : public UKerraWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleQuestWindow();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleInventoryWindow();

	
};
