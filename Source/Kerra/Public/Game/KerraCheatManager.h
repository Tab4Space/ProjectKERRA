// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "KerraCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class KERRA_API UKerraCheatManager : public UCheatManager
{
	GENERATED_BODY()

	UFUNCTION(Exec)
	void Console_ClearQuest(FString QuestTag);

	UFUNCTION(Exec)
	void Console_AddItem(FString ItemTag, int32 AddAmount = 1);

	UFUNCTION(Exec)
	void Console_AddGold(int32 AddAmount);

	UFUNCTION(Exec)
	void Console_ChangeSkillPoints(int32 InSkillPoints);
};
