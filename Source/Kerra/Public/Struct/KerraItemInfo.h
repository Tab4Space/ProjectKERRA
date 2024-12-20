#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "KerraItemInfo.generated.h"


USTRUCT(BlueprintType)
struct FKerraItemInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FKerraItemInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Item.ID"))
	FGameplayTag ItemIDTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemIDNumber;

	
};
