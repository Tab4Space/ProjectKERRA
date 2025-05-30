// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/KerraExtensionComponentBase.h"
#include "Struct/KerraQuestData.h"
#include "KerraQuestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddQuestSignature, FKerraQuestData, AddedQuestInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompleteQuestSignature, FKerraQuestData, CompletedQuest);

class UKerraWidgetBase;
class AKerraPlayerController;

UCLASS()
class KERRA_API UKerraQuestComponent : public UKerraExtensionComponentBase
{
	GENERATED_BODY()

public:
	/* Override */
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category="Quest|Player")
	bool AddQuest(FGameplayTag QuestIDTagToAdd);

	UFUNCTION(BlueprintCallable, Category="Quest|Player")
	void AddQuestNotification(EQuestNotification Notification, FKerraQuestData& QuestInfo);

	UFUNCTION(BlueprintCallable, Category="Quest|Player")
	void ClearQuest(FGameplayTag QuestTagToClear);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Quest|Npc")
	bool CheckClearCondition(FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Quest|Npc")
	float CheckQuestProgress(FGameplayTag QuestTagToCheck, FGameplayTag ObjectTag);

	UFUNCTION(BlueprintCallable, Category="Quest|Npc")
	bool GiveRewards(FGameplayTag QuestTag);
	
	/* Getter */
	UDataTable* GetQuestDataTable() { return QuestDataTable; }
	FGameplayTagContainer GetAcceptedQuestTags() { return AcceptedQuests; }
	FGameplayTagContainer GetCompletedQuestTags() { return CompletedQuests; }

public:
	UPROPERTY(BlueprintAssignable)
	FOnAddQuestSignature OnAddQuest;				// WBP_NotifyNewQuest

	UPROPERTY(BlueprintAssignable)
	FOnCompleteQuestSignature OnCompleteQuest;		// WBP_QuestWindow, WBP_TrackingQuest

private:
	TObjectPtr<AKerraPlayerController> KerraPC;
	
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UKerraWidgetBase> QuestNotificationWidgetClass;
	TObjectPtr<UKerraWidgetBase> QuestNotificationWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UKerraWidgetBase> QuestCompleteNotifyWidgetClass;
	TObjectPtr<UKerraWidgetBase> QuestCompleteNotifyWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UKerraWidgetBase> TrackQuestWidgetClass;
	TObjectPtr<UKerraWidgetBase> TrackQuestWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Quest")
	TObjectPtr<UDataTable> QuestDataTable;

	// Currently accepted quests
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quest|List", meta=(AllowPrivateAccess="true"))
	FGameplayTagContainer AcceptedQuests;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quest|List", meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, FKerraQuestData> AcceptedQuestsMap;

	// Already completed quests
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quest|List", meta=(AllowPrivateAccess="true"))
	FGameplayTagContainer CompletedQuests;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quest|List", meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, FKerraQuestData> CompletedQuestsMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	FKerraQuestData ActiveQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	TArray<FName> FailedQuest;

	bool bShowQuestWindow = false;
};
