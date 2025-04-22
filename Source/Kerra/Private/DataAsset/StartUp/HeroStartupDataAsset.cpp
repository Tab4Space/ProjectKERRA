// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartUp/HeroStartupDataAsset.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/KerraHeroAbility.h"


void UHeroStartupDataAsset::GiveToAbilitySystemComponent(UKerraAbilitySystemComponent* InASC, int32 InApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASC, InApplyLevel);

	/* Grant ability in HeroInputMappingAbilities */
	for(const FKerraPlayerAbilitySet& AbilitySet : HeroInputMappingAbilities)
	{
		if(!AbilitySet.IsValid())
		{
			continue;
		}
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASC->GetAvatarActor();
		AbilitySpec.Level = InApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		InASC->GiveAbility(AbilitySpec);
	}

	/* Grant ability in HeroUniqueAbilities */
	for(const TSubclassOf<UKerraGameplayAbility>& HeroUniqueAbility: HeroUniqueAbilities)
	{
		if(!HeroUniqueAbility)
		{
			continue;
		}
		
		FGameplayAbilitySpec AbilitySpec(HeroUniqueAbility);
		AbilitySpec.SourceObject = InASC->GetAvatarActor();
		AbilitySpec.Level = InApplyLevel;

		InASC->GiveAbility(AbilitySpec);
	}
}
