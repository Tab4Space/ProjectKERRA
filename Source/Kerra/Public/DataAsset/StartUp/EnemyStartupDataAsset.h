// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUp/KerraStartUpDataAssetBase.h"
#include "EnemyStartupDataAsset.generated.h"


class UKerraEnemyAbility;

UCLASS()
class KERRA_API UEnemyStartupDataAsset : public UKerraStartUpDataAssetBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UKerraAbilitySystemComponent* InASC, int32 InApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UKerraEnemyAbility>> EnemyCombatAbilities;
	
};
