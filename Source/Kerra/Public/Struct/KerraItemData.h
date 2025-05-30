#pragma once

#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "KerraItemData.generated.h"


UENUM(BlueprintType, Blueprintable)
enum class EItemType : uint8
{
	Equipment,
	Consumable,
	Material
};

USTRUCT(BlueprintType)
struct FKerraItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FKerraItemData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Item.ID"))
	FGameplayTag ItemIDTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemIDNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="ItemType!=EItemType::Equipment"))
	bool bStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bStackable"))
	int32 MaxCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Categories="Quest.ID"))
	FGameplayTagContainer AppliedQuest;

	bool IsValid() const;

	bool operator==(const FKerraItemData& Other) const
	{
		if(ItemIDTag != Other.ItemIDTag)
		{
			return false;
		}
		return true;
	}
};
