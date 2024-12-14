// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/KerraExtensionComponentBase.h"
#include "Struct/KerraQuestInfo.h"
#include "KerraQuestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddQuestDelegate, FKerraQuestInfo, AddedQuestInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveChanged, FKerraQuestInfo, TrackedQuest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotifyCompleteQuest, FKerraQuestInfo, CompletedQuest);

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
	void AddInQuestObjects(const FGameplayTag ObjectTag, const FGameplayTagContainer& UsedQuests);
	
	void AddQuestNotification(EQuestNotification Notification, FKerraQuestInfo& QuestInfo);

	UFUNCTION(BlueprintCallable)
	FGameplayTag TrackingQuest(FKerraQuestInfo QuestToTrack);
	
	/* Getter */
	UDataTable* GetQuestDataTable() { return QuestDataTable; }
	FGameplayTagContainer GetAcceptedQuestTags() { return AcceptedQuests; }
	FGameplayTagContainer GetCompletedQuestTags() { return CompletedQuests; }

	UFUNCTION()
	void ObjectiveUpdate(FKerraQuestInfo TrackedQuest);

public:
	UPROPERTY(BlueprintAssignable)
	FOnAddQuestDelegate OnAddQuest;

	UPROPERTY(BlueprintAssignable)
	FOnObjectiveChanged OnObjectiveChanged;

	UPROPERTY(BlueprintAssignable)
	FOnNotifyCompleteQuest OnNotifyCompleteQuest;

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
