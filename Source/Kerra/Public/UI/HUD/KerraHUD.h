// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KerraHUD.generated.h"

class UKerraDialogueWidget;
class UKerraOverlayWidget;
class UKerraQuestWidget;


UCLASS()
class KERRA_API AKerraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitMainOverlayWidget();

	UFUNCTION(BlueprintCallable)
	void CreateQuestWidget();

	UFUNCTION(BlueprintCallable)
	void CreateDialogueWidget();
	

	/* Getter */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraOverlayWidget* GetOverlayWidget() { return MainOverlayWidget; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraQuestWidget* GetQuestWidget() { return QuestWidget; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraDialogueWidget* GetDialogueWidget() { return DialogueWidget; }

private:
	UPROPERTY()
	TObjectPtr<UKerraOverlayWidget> MainOverlayWidget = nullptr;

	UPROPERTY(EditAnywhere, Category="WidgetClass")
	TSubclassOf<UKerraOverlayWidget> MainOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UKerraQuestWidget> QuestWidget = nullptr;

	UPROPERTY(EditAnywhere, Category="WidgetClass|Quest")
	TSubclassOf<UKerraQuestWidget> QuestWidgetClass;

	UPROPERTY()
	TObjectPtr<UKerraDialogueWidget> DialogueWidget = nullptr;

	UPROPERTY(EditAnywhere, Category="WidgetClass|Dialogue")
	TSubclassOf<UKerraDialogueWidget> DialogueWidgetClass;
	
	
};
