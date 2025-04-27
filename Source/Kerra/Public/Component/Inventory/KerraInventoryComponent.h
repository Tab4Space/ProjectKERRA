// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/KerraExtensionComponentBase.h"
#include "Struct/KerraItemInfo.h"
#include "KerraInventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddItemSignature, FGameplayTag, ItemTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeItemAmountSignature, FGameplayTag, ItemTag, int32, CurrentCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeGoldSignature, int32, CurrentGold);

UCLASS()
class KERRA_API UKerraInventoryComponent : public UKerraExtensionComponentBase
{
	GENERATED_BODY()

public:
	UKerraInventoryComponent();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool AddItem(FGameplayTag ItemIDTag, int32 AddAmount = 1);

	UFUNCTION(BlueprintCallable)
	void AddGold(int32 AddAmount);
	
	/* Getter */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FGameplayTagContainer GetOwningItemTags();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetCurrentItemCount(FGameplayTag ItemIDTag);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetCurrentGold();

public:
	UPROPERTY(BlueprintAssignable)
	FAddItemSignature OnAddItem;
	
	UPROPERTY(BlueprintAssignable)
	FOnChangeItemAmountSignature OnChangeItemAmount;

	UPROPERTY(BlueprintAssignable)
	FOnChangeGoldSignature OnChangeGold;

private:
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TObjectPtr<UDataTable> ItemDataTable;
	
	UPROPERTY(VisibleAnywhere, Category="Inventory|Item", meta=(Categories="Item.ID"))
	FGameplayTagContainer OwningItemTags;

	UPROPERTY(VisibleAnywhere, Category="Inventory|Item", meta=(Categories="Item.ID"))
	TMap<FGameplayTag, FKerraItemInfo> OwningItemMaps;

	UPROPERTY(VisibleAnywhere, Category="Inventory|Gold", meta=(AllowPrivateAccess))
	int32 CurrentGolds;

	
	
};
