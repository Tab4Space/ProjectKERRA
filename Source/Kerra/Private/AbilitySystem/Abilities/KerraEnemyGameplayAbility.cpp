// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraEnemyGameplayAbility.h"
#include "Character/KerraEnemy.h"
#include "AbilitySystem/Abilities/KerraEnemyGameplayAbility.h"
#include "Component/Combat/KerraEnemyCombatComponent.h"

AKerraEnemy* UKerraEnemyGameplayAbility::GetEnemyActorInfo()
{
	if(!CachedKerraEnemy.IsValid())
	{
		CachedKerraEnemy = Cast<AKerraEnemy>(CurrentActorInfo->AvatarActor);
	}
	return CachedKerraEnemy.IsValid() ? CachedKerraEnemy.Get() : nullptr;
}

UKerraEnemyCombatComponent* UKerraEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyActorInfo()->GetEnemyCombatComponent();
}
