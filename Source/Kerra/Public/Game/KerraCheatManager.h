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
};
