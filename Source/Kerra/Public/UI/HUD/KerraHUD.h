// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KerraHUD.generated.h"

class UKerraQuestWidget;
class UKerraWidgetBase;

UCLASS()
class KERRA_API AKerraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitMainOverlayWidget();

	/* Getter */
	

private:
	UPROPERTY()
	TObjectPtr<UKerraWidgetBase> MainOverlayWidget;

	UPROPERTY(EditAnywhere, Category="WidgetClass")
	TSubclassOf<UKerraWidgetBase> MainOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UKerraQuestWidget> QuestWindowWidget;

	UPROPERTY(EditAnywhere, Category="WidgetClass|Quest")
	TSubclassOf<UKerraQuestWidget> QuestWindowWidgetClass;
	
	
};
