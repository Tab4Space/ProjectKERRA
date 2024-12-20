// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/KerraExtensionComponentBase.h"
#include "Struct/KerraItemInfo.h"
#include "KerraInventoryComponent.generated.h"


UCLASS()
class KERRA_API UKerraInventoryComponent : public UKerraExtensionComponentBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool AddItem(FGameplayTag ItemID);

private:
	UPROPERTY(VisibleAnywhere, Category="Inventory|Item", meta=(Categories="Item.ID"))
	FGameplayTagContainer OwningItemTags;

	UPROPERTY(VisibleAnywhere, Category="Inventory|Item", meta=(Categories="Item.ID"))
	TMap<FGameplayTag, FKerraItemInfo> OwningItemMaps;
	
};
