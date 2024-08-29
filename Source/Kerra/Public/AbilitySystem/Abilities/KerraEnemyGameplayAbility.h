// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KerraGameplayAbility.h"
#include "KerraEnemyGameplayAbility.generated.h"


class AKerraEnemy;
class UKerraEnemyCombatComponent;

UCLASS()
class KERRA_API UKerraEnemyGameplayAbility : public UKerraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	AKerraEnemy* GetEnemyActorInfo();

	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	UKerraEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AKerraEnemy> CachedKerraEnemy;
};
