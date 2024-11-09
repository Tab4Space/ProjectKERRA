// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/KerraExtensionComponentBase.h"
#include "Struct/KerraQuestInfo.h"
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

	UFUNCTION(BlueprintCallable)
	bool AddQuest(FKerraQuestInfo AddQuestInfo);
	bool CanAcceptQuest(FKerraQuestInfo CheckQuestInfo);
	bool CheckCompletedQuest(FKerraQuestInfo CheckQuestInfo);

private:
	TObjectPtr<AKerraPlayerController> KerraPC;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UKerraWidgetBase> QuestWidgetClass;
	
	TObjectPtr<UKerraWidgetBase> QuestWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	TArray<FKerraQuestInfo> AcceptedQuests;

	UPROPERTY(EditDefaultsOnly, Category="Quest")
	FKerraQuestInfo ActiveQuest;

	UPROPERTY(EditDefaultsOnly, Category="Quest")
	TArray<FName> CompletedQuest;

	UPROPERTY(EditDefaultsOnly, Category="Quest")
	TArray<FName> FailedQuest;
};
