// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraEnemyAbility.h"
#include "Character/KerraEnemy.h"
#include "AbilitySystem/Abilities/KerraEnemyAbility.h"
#include "Component/Combat/EnemyCombatComponent.h"

AKerraEnemy* UKerraEnemyAbility::GetEnemyActorInfo()
{
	if(!CachedKerraEnemy.IsValid())
	{
		CachedKerraEnemy = Cast<AKerraEnemy>(CurrentActorInfo->AvatarActor);
	}
	return CachedKerraEnemy.IsValid() ? CachedKerraEnemy.Get() : nullptr;
}

UEnemyCombatComponent* UKerraEnemyAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyActorInfo()->GetEnemyCombatComponent();
}
