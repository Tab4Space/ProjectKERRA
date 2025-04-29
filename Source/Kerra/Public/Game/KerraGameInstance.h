// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KerraGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KERRA_API UKerraGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
	UDataTable* GetQuestDataTable() { return QuestDataTable; };
	
	UFUNCTION()
	UDataTable* GetItemDataTable() { return ItemDataTable; };

private:
	UPROPERTY(EditDefaultsOnly, Category="Quest")
	TObjectPtr<UDataTable> QuestDataTable;

	UPROPERTY(EditDefaultsOnly, Category="Item")
	TObjectPtr<UDataTable> ItemDataTable;
};
