// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "KerraQuestInfo.generated.h"

UENUM()
enum class EQuestType : uint8
{
	MainQuest,
	SubQuest
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
	FName ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ObjectiveDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> ObjectiveTips;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequireAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasMarker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bObjectiveCompleteAnotherQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer QuestIDs;
	//TArray<EQuestName> QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestItemName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestArea AreaLocation;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestType QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRepeatable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestObjective> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestGiver QuestGiver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag NextQuestID;
	//EQuestName GiveNextQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuestReward QuestReward;

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

