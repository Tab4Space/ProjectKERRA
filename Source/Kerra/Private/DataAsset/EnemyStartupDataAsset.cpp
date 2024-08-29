// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/EnemyStartupDataAsset.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/KerraEnemyGameplayAbility.h"

void UEnemyStartupDataAsset::GiveToAbilitySystemComponent(UKerraAbilitySystemComponent* InASC, int32 InApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASC, InApplyLevel);

	if(!EnemyCombatAbilities.IsEmpty())
	{
		for(const TSubclassOf<UKerraEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if(!AbilityClass)
			{
				continue;
			}

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASC->GetAvatarActor();
			AbilitySpec.Level = InApplyLevel;
			
			InASC->GiveAbility(AbilitySpec);
		}
	}
}
