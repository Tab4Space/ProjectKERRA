// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/KerraDialogueWidget.h"
#include "UI/Widget/KerraInventoryWidget.h"
#include "KerraHUD.generated.h"

class UKerraAttributeSet;
class UKerraAbilitySystemComponent;
class AKerraPlayerState;
class AKerraPlayerController;
class UKerraDialogueWidget;
class UKerraOverlayWidget;
class UKerraQuestWidget;
class UKerraInventoryWidget;

UCLASS()
class KERRA_API AKerraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitMainOverlayWidget(AKerraPlayerController* PC, AKerraPlayerState* PS, UKerraAbilitySystemComponent* ASC ,UKerraAttributeSet* AS);

	UFUNCTION(BlueprintCallable)
	void CreateQuestWidget();

	UFUNCTION(BlueprintCallable)
	void CreateDialogueWidget();

	UFUNCTION(BlueprintCallable)
	void CreateInventoryWidget();

	/* Setter */
	UFUNCTION(BlueprintCallable)
	void SetPlayerOverlayWidget(UKerraOverlayWidget* InPlayerOverlayWidget);

	UFUNCTION(BlueprintCallable)
	void SetInventoryOverlayWidget(UKerraOverlayWidget* InInventoryOverlayWidget);

	UFUNCTION(BlueprintCallable)
	void SetQuestOverlayWidget(UKerraOverlayWidget* InQuestOverlayWidget);

	UFUNCTION(BlueprintCallable)
	void SetSkillOverlayWidget(UKerraOverlayWidget* InSkillOverlayWidget);

	UFUNCTION(BlueprintCallable)
	void SetWorldMapOverlayWidget(UKerraOverlayWidget* InWorldMapOverlayWidget);

	/* Getter */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraOverlayWidget* GetMainOverlayWidget() { return MainOverlayWidget; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraOverlayWidget* GetPlayerOverlayWidget() { return PlayerOverlayWidget; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraOverlayWidget* GetInventoryOverlayWidget() { return InventoryOverlayWidget; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraOverlayWidget* GetQuestOverlayWidget() { return QuestOverlayWidget; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraOverlayWidget* GetSkillOverlayWidget() { return SkillOverlayWidget; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraOverlayWidget* GetWorldMapOverlayWidget() { return WorldMapOverlayWidget; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraQuestWidget* GetQuestWidget() { return QuestWidget; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraDialogueWidget* GetDialogueWidget() { return DialogueWidget; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UKerraInventoryWidget* GetInventoryWidget() { return InventoryWidget; }

	AKerraPlayerController* GetKerraPlayerController() { return KerraPC; }
	AKerraPlayerState* GetKerraPlayerState() { return KerraPS; }
	UKerraAbilitySystemComponent* GetKerraAbilitySystemComponent() { return KerraASC; }
	UKerraAttributeSet* GetKerraAttributeSet() { return KerraAS; }

private:
	UPROPERTY()
	TObjectPtr<UKerraOverlayWidget> MainOverlayWidget = nullptr;
	UPROPERTY(EditAnywhere, Category="WidgetClass|Overlay")
	TSubclassOf<UKerraOverlayWidget> MainOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UKerraOverlayWidget> PlayerOverlayWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UKerraOverlayWidget> InventoryOverlayWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UKerraOverlayWidget> QuestOverlayWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UKerraOverlayWidget> SkillOverlayWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UKerraOverlayWidget> WorldMapOverlayWidget = nullptr;


	UPROPERTY()
	TObjectPtr<UKerraQuestWidget> QuestWidget = nullptr;
	UPROPERTY(EditAnywhere, Category="WidgetClass|Window")
	TSubclassOf<UKerraQuestWidget> QuestWidgetClass;

	UPROPERTY()
	TObjectPtr<UKerraDialogueWidget> DialogueWidget = nullptr;
	UPROPERTY(EditAnywhere, Category="WidgetClass|Window")
	TSubclassOf<UKerraDialogueWidget> DialogueWidgetClass;

	UPROPERTY()
	TObjectPtr<UKerraInventoryWidget> InventoryWidget = nullptr;
	UPROPERTY(EditAnywhere, Category="WidgetClass|Window")
	TSubclassOf<UKerraInventoryWidget> InventoryWidgetClass;

	UPROPERTY()
	TObjectPtr<AKerraPlayerController> KerraPC = nullptr;

	UPROPERTY()
	TObjectPtr<AKerraPlayerState> KerraPS = nullptr;

	UPROPERTY()
	TObjectPtr<UKerraAbilitySystemComponent> KerraASC = nullptr;

	UPROPERTY()
	TObjectPtr<UKerraAttributeSet> KerraAS = nullptr;
	
};
