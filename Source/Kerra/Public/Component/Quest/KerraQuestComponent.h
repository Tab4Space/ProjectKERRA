// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/KerraExtensionComponentBase.h"
#include "Struct/KerraQuestInfo.h"
#include "KerraQuestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddQuestDelegate, FKerraQuestInfo, AddedQuestInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveChanged, FKerraQuestInfo, TrackedQuest);

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
	bool AddQuest(FGameplayTag QuestIDTagToAdd);

	UFUNCTION(BlueprintCallable)
	void AddItemInQuestObjectives(const FGameplayTag ItemIDTag, const FGameplayTagContainer& UsedQuests);
	

	UFUNCTION(BlueprintCallable)
	void AddItemToQuestObjective(EQuestItemName ItemName, ENpcName NpcName, EQuestArea Area);

	UFUNCTION(BlueprintCallable)
	void CanCompleteQuest(const FKerraQuestInfo QuestInfo, const EQuestClearType ClearType);

	UFUNCTION(BlueprintCallable)
	void FindQuestID(EQuestItemName ItemName, ENpcName NpcName, EQuestArea Area, bool& OutFound, FGameplayTag& OutQuestID, int32& OutQuestIndex, FKerraQuestInfo& OutQuestInfo);

	UFUNCTION(BlueprintCallable)
	bool GetCurrentObjective(FKerraQuestInfo QuestInfo, FQuestObjective& OutObjective, int32& OutObjectiveIndex);

	UFUNCTION(BlueprintCallable)
	FKerraQuestInfo GetQuestInfoFromQuestName(const FName QuestName, bool& OutIsFound);
	
	void AddQuestNotification(EQuestNotification Notification, FKerraQuestInfo& QuestInfo);

	UFUNCTION(BlueprintCallable)
	bool CanQuestCompleted(const FKerraQuestInfo& QuestToCheck, FKerraQuestInfo& OutCheckedQuest);

	void CompleteQuest(FKerraQuestInfo QuestToComplete);

	UFUNCTION(BlueprintCallable)
	FGameplayTag TrackingQuest(FKerraQuestInfo QuestToTrack);
	
	/* Getter */
	UDataTable* GetQuestDataTable() { return QuestDataTable; }

	UFUNCTION()
	void ObjectiveUpdate(FKerraQuestInfo TrackedQuest);

public:
	UPROPERTY(BlueprintAssignable)
	FOnAddQuestDelegate OnAddQuest;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveChanged OnObjectiveChanged;

private:
	TObjectPtr<AKerraPlayerController> KerraPC;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UKerraWidgetBase> QuestWidgetClass;
	TObjectPtr<UKerraWidgetBase> QuestWidget = nullptr;

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
	TMap<FGameplayTag, FKerraQuestInfo> AcceptedQuestsMap;

	// Already completed quests
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quest|List", meta=(AllowPrivateAccess="true"))
	FGameplayTagContainer CompletedQuests;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Quest|List", meta=(AllowPrivateAccess="true"))
	TMap<FGameplayTag, FKerraQuestInfo> CompletedQuestsMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	FKerraQuestInfo ActiveQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Quest", meta=(AllowPrivateAccess="true"))
	TArray<FName> FailedQuest;

	bool bShowQuestWindow = false;
};
