// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/KerraExtensionComponentBase.h"
#include "Struct/KerraItemInfo.h"
#include "KerraInventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddItemSigniture, FGameplayTag, ItemTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangeItemCountSigniture, FGameplayTag, ItemTag, int32, CurrentCount);

UCLASS()
class KERRA_API UKerraInventoryComponent : public UKerraExtensionComponentBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool AddItem(FGameplayTag ItemID);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetCurrentItemCount(FGameplayTag ItemIDTag);

public:
	UPROPERTY(BlueprintAssignable)
	FAddItemSigniture OnAddItem;
	
	UPROPERTY(BlueprintAssignable)
	FChangeItemCountSigniture OnChangeItemCount;

private:
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TObjectPtr<UDataTable> ItemDataTable;
	
	UPROPERTY(VisibleAnywhere, Category="Inventory|Item", meta=(Categories="Item.ID"))
	FGameplayTagContainer OwningItemTags;

	UPROPERTY(VisibleAnywhere, Category="Inventory|Item", meta=(Categories="Item.ID"))
	TMap<FGameplayTag, FKerraItemInfo> OwningItemMaps;
	
};