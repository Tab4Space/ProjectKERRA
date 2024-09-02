// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUp/EnemyStartupDataAsset.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/KerraEnemyAbility.h"

void UEnemyStartupDataAsset::GiveToAbilitySystemComponent(UKerraAbilitySystemComponent* InASC, int32 InApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASC, InApplyLevel);

	if(!EnemyCombatAbilities.IsEmpty())
	{
		for(const TSubclassOf<UKerraEnemyAbility>& AbilityClass : EnemyCombatAbilities)
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
