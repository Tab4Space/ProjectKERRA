// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/KerraExtensionComponentBase.h"
#include "KerraQuestComponent.generated.h"

class UKerraWidgetBase;
class AKerraPlayerController;


UCLASS()
class KERRA_API UKerraQuestComponent : public UKerraExtensionComponentBase
{
	GENERATED_BODY()

public:
	/* Override */
	virtual void BeginPlay() override;
	
	void ToggleQuestWidget();

private:
	TObjectPtr<AKerraPlayerController> KerraPC;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UKerraWidgetBase> QuestWidgetClass;
	
	TObjectPtr<UKerraWidgetBase> QuestWidget = nullptr;
};
