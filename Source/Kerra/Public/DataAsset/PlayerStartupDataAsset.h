// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAsset/StartupDataAssetBase.h"
#include "PlayerStartupDataAsset.generated.h"


class UKerraGameplayAbility;

USTRUCT(BlueprintType)
struct FKerraPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UKerraGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

UCLASS()
class KERRA_API UPlayerStartupDataAsset : public UStartupDataAssetBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UKerraAbilitySystemComponent* InASC, int32 InApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartupData", meta=(TitleProperty="InputTag"))
	TArray<FKerraPlayerAbilitySet> KerraPlayerStartupAbilitySets;
};

