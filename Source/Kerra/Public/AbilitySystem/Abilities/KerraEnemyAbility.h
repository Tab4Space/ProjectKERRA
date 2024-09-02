// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KerraGameplayAbility.h"
#include "KerraEnemyAbility.generated.h"


class AKerraEnemy;
class UEnemyCombatComponent;

UCLASS()
class KERRA_API UKerraEnemyAbility : public UKerraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	AKerraEnemy* GetEnemyActorInfo();

	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AKerraEnemy> CachedKerraEnemy;
};
