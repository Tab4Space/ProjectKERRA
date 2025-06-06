﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "KerraQuestData.generated.h"

UENUM()
enum class EQuestCategory : uint8
{
	MainQuest,
	SubQuest
};

UENUM()
enum class EQuestClearType : uint8
{
	None,
	CollectItem,
	KillEnemy,
	GoToLocation,
	TalkToNpc
};

UENUM(BlueprintType, Blueprintable)
enum class EQuestFilter : uint8
{
	All,
	Ongoing,
	Completed
};

UENUM(BlueprintType, Blueprintable)
enum class EQuestNotification : uint8
{
	None,
	NewQuest,
	CompletedQuest,
	FailedQuest
};

USTRUCT(BlueprintType)
struct FQuestReward
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GiveXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GiveGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Item.ID"))
	TMap<FGameplayTag, int32> GiveItem;
};


USTRUCT(BlueprintType)
struct FKerraQuestData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	FKerraQuestData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Quest.ID"))
	FGameplayTag QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// quest type (main or side)
	EQuestCategory QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// kill, collect, go to, talking
	EQuestClearType QuestClearType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// quest name
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// quest description
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DialogueText;					// dialogue text

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// is repeatable?
	bool bRepeatable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, int32> RequireObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="NPC.ID") )
	FGameplayTag QuestGiver;						// quest giver

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Quest.ID"))
	FGameplayTag PreviousQuestID;					// previous quest id (if previous quest isn't completed, not receive quest)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Quest.ID"))
	FGameplayTag NextQuestID;						// next quest

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuestReward QuestReward;
	

	// 이것도 tag로 바꿔야할듯?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Location.ID"))
	FGameplayTag QuestLocation;
	
	bool IsValid() const;

	bool operator==(const FKerraQuestData& Other) const
	{
		if(QuestID != Other.QuestID)
		{
			return false;
		}
		return true;
	}
};

