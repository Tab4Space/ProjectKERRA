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

	// FScopedAbilityLock으로 mutable 방지, 활성 가능한 모든 ability를 체크하고
	FScopedAbilityListLock ActiveScopeLock(*this);
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

	FScopedAbilityListLock ActiveScopeLock(*this);
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

FGameplayTag UKerraAbilitySystemComponent::GrantAbilityWithInputTag(TSubclassOf<UKerraGameplayAbility> AbilityClass, int32 ApplyLevel, FGameplayTag InInputTag)
{
	// Check that ability is already granted ability or not
	FGameplayAbilitySpec AbilitySpec(AbilityClass);
	FGameplayTag AbilityTag = AbilitySpec.Ability->AbilityTags.First();

	FScopedAbilityListLock ActiveScopeLock(*this);
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTag.GetSingleTagContainer(), FoundAbilitySpecs);
	if(!FoundAbilitySpecs.IsEmpty())
	{
		KERRALOG(Warning, TEXT("%s is already granted"), *AbilityClass->GetDisplayNameText().ToString());
		return FGameplayTag();
	}
	
	AbilitySpec.SourceObject = GetAvatarActor();
	AbilitySpec.Level = ApplyLevel;
	AbilitySpec.DynamicAbilityTags.AddTag(InInputTag);
	GiveAbility(AbilitySpec);
	return AbilitySpec.Ability->AbilityTags.First();
}

void UKerraAbilitySystemComponent::RemoveAbilityByTag(FGameplayTag InTagToRemove)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(InTagToRemove.GetSingleTagContainer(), FoundAbilitySpecs);
	if(FoundAbilitySpecs.IsEmpty())
	{
		KERRALOG(Warning, TEXT("Not valid ability %s"), *InTagToRemove.ToString())
		return;
	}

	ClearAbility(FoundAbilitySpecs[0]->Handle);
}

bool UKerraAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	// 해당 함수에서 어떤 ability가 결과로 나오려면 ASC에 부여(give)된 상태여야 한다.
	FScopedAbilityListLock ActiveScopeLock(*this);
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
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

bool UKerraAbilitySystemComponent::GetAbilitySpecFromTag(const FGameplayTag InAbilityTag, FGameplayAbilitySpec& OutSpec)
{
	FScopedAbilityListLock ActivateScopeLock(*this);
	for(FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// AbilitySpec.Ability.Get()->AbilityTags.First();
		for(FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if(Tag.MatchesTag(InAbilityTag))
			{
				OutSpec = AbilitySpec;
				return true;
			}
		}
	}
	return false;
}
