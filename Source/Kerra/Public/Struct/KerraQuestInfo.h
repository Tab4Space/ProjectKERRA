// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "KerraQuestInfo.generated.h"

USTRUCT(BlueprintType)
struct FKerraQuestInfo
{
	GENERATED_BODY()

	bool IsValid() const;
};