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

	UFUNCTION(BlueprintCallable)
	void ToggleQuestWidget();

	UFUNCTION(BlueprintCallable)
	bool AddQuest(FKerraQuestInfo AddQuestInfo);
	bool CanAcceptQuest(FKerraQuestInfo CheckQuestInfo);
	bool CheckCompletedQuest(FKerraQuestInfo CheckQuestInfo);

	UFUNCTION(BlueprintCallable)
	FKerraQuestInfo GetQuestInfoFromQuestName(const FName QuestName, bool& OutIsFound);

private:
	TObjectPtr<AKerraPlayerController> KerraPC;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UKerraWidgetBase> QuestWidgetClass;
	
	TObjectPtr<UKerraWidgetBase> QuestWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Quest")
	TObjectPtr<UDataTable> QuestDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	TArray<FKerraQuestInfo> AcceptedQuests;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	FKerraQuestInfo ActiveQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	TArray<FName> CompletedQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	TArray<FName> FailedQuest;
};
