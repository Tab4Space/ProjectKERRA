// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct/KerraQuestData.h"
#include "UI/Widget/KerraWidgetBase.h"
#include "KerraOverlayWidget.generated.h"

class UKerraAttributeSet;
class UKerraAbilitySystemComponent;
class AKerraPlayerState;
class AKerraPlayerController;
class AKerraHero;
class AKerraNpc;

UCLASS()
class KERRA_API UKerraOverlayWidget : public UKerraWidgetBase
{
	GENERATED_BODY()

public:
	/* Quest */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddQuestTrackingWindow(FKerraQuestData QuestInfo);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveQuestTrackingWindow(FKerraQuestData QuestInfo);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddQuestWindow();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddDialogueWindow();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddQuestNotifyWindow(EQuestNotification NotifyType);

	/* Inventory */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddInventoryWindow();

private:
	UPROPERTY()
	TObjectPtr<AKerraPlayerController> KerraPC;

	UPROPERTY()
	TObjectPtr<AKerraPlayerState> KerraPS;

	UPROPERTY()
	TObjectPtr<UKerraAbilitySystemComponent> KerraASC;

	UPROPERTY()
	TObjectPtr<UKerraAttributeSet> KerraAS;
	
};
