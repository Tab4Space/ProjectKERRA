// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/KerraHeroAbility.h"
#include "KerraGameplayTags.h"
#include "Kerra/Kerra.h"

void UKerraAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid())
	{
		return;
	}

	// 활성 가능한 모든 ability를 체크하고
	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			continue;
		}

		if(InInputTag.MatchesTag(KerraGameplayTags::InputTag_Toggleable) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UKerraAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid() || !InInputTag.MatchesTag(KerraGameplayTags::InputTag_MustBeHeld))
	{
		return;
	}

	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}

void UKerraAbilitySystemComponent::GrantWeaponAbilities(const TArray<FKerraPlayerAbilitySet>& InDefaultWeaponAbilities, const TArray<FKerraPlayerSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if(InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	for(const FKerraPlayerAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if(!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}

	for(const FKerraPlayerSpecialAbilitySet& AbilitySet : InSpecialWeaponAbilities)
	{
		if(!AbilitySet.IsValid())
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UKerraAbilitySystemComponent::RemoveGrantedWeaponAbilities(TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if(InSpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for(const FGameplayAbilitySpecHandle SpecHandle : InSpecHandlesToRemove)
	{
		if(SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}
	InSpecHandlesToRemove.Empty();
}

FGameplayAbilitySpec UKerraAbilitySystemComponent::GrantAbilityWithTags(TSubclassOf<UKerraGameplayAbility> AbilityClass, int32 ApplyLevel, FGameplayTagContainer AddedTags)
{
	// Check that ability is already granted ability or not
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AddedTags, FoundAbilitySpecs);
	if(!FoundAbilitySpecs.IsEmpty())
	{
		KERRALOG(Warning, TEXT("%s is already granted"), *AbilityClass->GetDisplayNameText().ToString());
		return FGameplayAbilitySpec();
	}
	
	FGameplayAbilitySpec AbilitySpec(AbilityClass);
	AbilitySpec.SourceObject = GetAvatarActor();
	AbilitySpec.Level = ApplyLevel;
	FGameplayTag AbilityTag = AbilitySpec.Ability->AbilityTags.First();
	KERRALOG(Warning, TEXT("Granted AbilityTag: %s"), *AbilityTag.ToString());

	for(const FGameplayTag Tag : AddedTags)
	{
		AbilitySpec.DynamicAbilityTags.AddTag(Tag);
	}
	GiveAbility(AbilitySpec);
	return AbilitySpec;
	
	/*
	for(auto a : AbilitySpec.Ability->AbilityTags)
	{
		KERRALOG(Warning, TEXT("%s"), *a.ToString());
	}
	GiveAbility(AbilitySpec);*/
}

void UKerraAbilitySystemComponent::RemoveAbilityByTag(FGameplayTag InTagToRemove)
{
	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InTagToRemove))
		{
			//KERRALOG(Warning, TEXT("%s"), AbilitySpec.Ability->)
			ClearAbility(AbilitySpec.Handle);
		}
	}
}

bool UKerraAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;

	// 해당 함수에서 어떤 ability가 결과로 나오려면 ASC에 부여(give)된 상태여야 한다.
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if(!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num()-1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(SpecToActivate);

		if(!SpecToActivate->IsActive())
		{
			KERRALOG(Warning, TEXT("%s"), *SpecToActivate->Ability->AbilityTags.ToString())
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}
	return false;
}
