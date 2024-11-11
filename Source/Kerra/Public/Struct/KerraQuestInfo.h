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
enum class EQuestName : uint8
{
	None,
	Welcome,
	SecondQuest
};

UENUM()
enum class EQuestGiver : uint8
{
	None
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
	None
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
enum EQuestNotification
{
	None,
	NewQuest,
	CompletedQuest,
	FailedQuest
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
	TArray<EQuestName> QuestID;

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
	EQuestName QuestID;

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
	EQuestName GiveNextQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuestReward QuestReward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestArea QuestLocation;
	
	bool IsValid() const;
};

