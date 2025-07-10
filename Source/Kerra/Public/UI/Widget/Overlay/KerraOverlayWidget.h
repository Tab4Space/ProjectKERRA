// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystem/KerraAttributeSet.h"
#include "Player/KerraPlayerState.h"
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

	/* Set parameters */
	void SetParams(AKerraPlayerController* PC, AKerraPlayerState* PS, UKerraAbilitySystemComponent* ASC, UKerraAttributeSet* AS);

	/* Getter */
	UFUNCTION(BlueprintPure)
	AKerraPlayerController* GetKerraPC() { return KerraPC; }
	
	UFUNCTION(BlueprintPure)
	AKerraPlayerState* GetKerraPS() { return KerraPS; }

	UFUNCTION(BlueprintPure)
	UKerraAbilitySystemComponent* GetKerraASC() { return KerraASC; }

	UFUNCTION(BlueprintPure)
	UKerraAttributeSet* GetKerraAS() { return KerraAS; }

	/* Bind events */
	virtual void BindEvents();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UKerraOverlayWidget> ParentOverlayWidget = nullptr;
	
private:
	UPROPERTY()
	TObjectPtr<AKerraPlayerController> KerraPC = nullptr;

	UPROPERTY()
	TObjectPtr<AKerraPlayerState> KerraPS = nullptr;

	UPROPERTY()
	TObjectPtr<UKerraAbilitySystemComponent> KerraASC = nullptr;

	UPROPERTY()
	TObjectPtr<UKerraAttributeSet> KerraAS = nullptr;
	
};
