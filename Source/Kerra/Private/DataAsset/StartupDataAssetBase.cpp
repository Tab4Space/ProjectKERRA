// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/StartupDataAssetBase.h"
#include "AbilitySystem/Abilities/KerraGameplayAbility.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"

void UStartupDataAssetBase::GiveToAbilitySystemComponent(UKerraAbilitySystemComponent* InASC, int32 InApplyLevel)
{
	checkf(InASC, TEXT("Not valid ability system component"));

	GrantAbilities(ActivateOnGivenAbilities, InASC, InApplyLevel);
	GrantAbilities(ReactiveAbilities, InASC, InApplyLevel);
}

void UStartupDataAssetBase::GrantAbilities(const TArray<TSubclassOf<UKerraGameplayAbility>>& InAbilitiesToGive, UKerraAbilitySystemComponent* InASC, int32 InApplyLevel)
{
	if(InAbilitiesToGive.IsEmpty())
		return;

	for(const TSubclassOf<UKerraGameplayAbility>& Ability: InAbilitiesToGive)
	{
		if(!Ability)
			continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASC->GetAvatarActor();
		AbilitySpec.Level = InApplyLevel;
		
		InASC->GiveAbility(AbilitySpec);
	}
}