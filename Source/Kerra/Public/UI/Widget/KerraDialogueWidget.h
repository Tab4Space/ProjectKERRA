// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/KerraWidgetBase.h"
#include "Struct/KerraQuestData.h"
#include "KerraDialogueWidget.generated.h"

class AKerraHero;
class AKerraNpc;

UCLASS()
class KERRA_API UKerraDialogueWidget : public UKerraWidgetBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetQuestInfo(AActor* InNpcActor, AActor* InPlayerActor, FKerraQuestData InQuestInfo);

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetFirstDialogueText();

protected:
	UPROPERTY(BlueprintReadOnly, Category="QuestInfo")
	AKerraNpc* NpcActor;

	UPROPERTY(BlueprintReadOnly, Category="QuestInfo")
	AKerraHero* PlayerActor;

	UPROPERTY(BlueprintReadOnly, Category="QuestInfo")
	FKerraQuestData QuestInfo;
};
