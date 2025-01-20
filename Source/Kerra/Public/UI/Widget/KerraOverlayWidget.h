// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct/KerraQuestInfo.h"
#include "UI/Widget/KerraWidgetBase.h"
#include "KerraOverlayWidget.generated.h"

class AKerraHero;
class AKerraNpc;
/**
 * 
 */
UCLASS()
class KERRA_API UKerraOverlayWidget : public UKerraWidgetBase
{
	GENERATED_BODY()

public:
	/* Quest */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddQuestTrackingWindow(FKerraQuestInfo QuestInfo);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveQuestTrackingWindow(FKerraQuestInfo QuestInfo);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddDialogueWindow(AKerraNpc* CallNpc, AKerraHero* Target);

	
};
