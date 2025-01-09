// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KerraHUD.generated.h"

class UKerraOverlayWidget;
class UKerraQuestWidget;


UCLASS()
class KERRA_API AKerraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitMainOverlayWidget();

	UFUNCTION()
	void CreateQuestWidget();
	

	/* Getter */
	UFUNCTION(BlueprintCallable)
	UKerraOverlayWidget* GetOverlayWidget() { return MainOverlayWidget; }

	UFUNCTION(BlueprintCallable)
	UKerraQuestWidget* GetQuestWidget() { return QuestWidget; }

private:
	UPROPERTY()
	TObjectPtr<UKerraOverlayWidget> MainOverlayWidget = nullptr;

	UPROPERTY(EditAnywhere, Category="WidgetClass")
	TSubclassOf<UKerraOverlayWidget> MainOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UKerraQuestWidget> QuestWidget = nullptr;

	UPROPERTY(EditAnywhere, Category="WidgetClass|Quest")
	TSubclassOf<UKerraQuestWidget> QuestWidgetClass;
	
	
};
