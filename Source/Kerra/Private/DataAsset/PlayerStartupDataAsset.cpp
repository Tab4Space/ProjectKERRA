// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/PlayerStartupDataAsset.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/KerraPlayerGameplayAbility.h"


void UPlayerStartupDataAsset::GiveToAbilitySystemComponent(UKerraAbilitySystemComponent* InASC, int32 InApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASC, InApplyLevel);

	for(const FKerraPlayerAbilitySet& AbilitySet : KerraPlayerStartupAbilitySets)
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
}