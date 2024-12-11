// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "KerraQuestInfo.generated.h"

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

UENUM()
enum class EQuestGiver : uint8
{
	None,
	Jone,
	Bob,
	Matt,
	Test
};

UENUM()
enum class EQuestItemName : uint8
{
	None,
	Apple
};

UENUM()
enum class EQuestArea : uint8
{
	None,
	FirstLocation
};

UENUM(BlueprintType, Blueprintable)
enum class EQuestFilter : uint8
{
	None,
	MainQuest,
	SubQuest,
	CompletedQuest,
	FailedQuest
};

UENUM()
enum class EQuestNotification : uint8
{
	None,
	NewQuest,
	CompletedQuest,
	FailedQuest
};

UENUM()
enum class ENpcName : uint8
{
	None,
};

USTRUCT(BlueprintType)
struct FQuestObjective
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ObjectiveDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequireAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasMarker;
};

USTRUCT(BlueprintType)
struct FQuestReward
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 XP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EQuestItemName, int32> Item;
};


USTRUCT(BlueprintType)
struct FKerraQuestInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	FKerraQuestInfo();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		// is repeatable?
	bool bRepeatable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, FQuestObjective> RequireObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="NPC.ID") )
	FGameplayTag QuestGiver;						// quest giver

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Quest.ID"))
	FGameplayTag PreviousQuestID;					// previous quest id (if previous quest isn't completed, not receive quest)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Quest.ID"))
	FGameplayTag NextQuestID;						// next quest

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuestReward QuestReward;						

	// 이것도 tag로 바꿔야할듯?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestArea QuestLocation;
	
	bool IsValid() const;

	bool operator==(const FKerraQuestInfo& Other) const
	{
		if(QuestID != Other.QuestID)
		{
			return false;
		}
		return true;
	}
};

