// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartupDataAssetBase.h"
#include "EnemyStartupDataAsset.generated.h"


class UKerraEnemyGameplayAbility;

UCLASS()
class KERRA_API UEnemyStartupDataAsset : public UStartupDataAssetBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UKerraAbilitySystemComponent* InASC, int32 InApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UKerraEnemyGameplayAbility>> EnemyCombatAbilities;
	
};
