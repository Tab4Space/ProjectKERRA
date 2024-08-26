// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/KerraAbilitySystemComponent.h"

void UKerraAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	UE_LOG(LogTemp, Warning, TEXT("On Abilty Input Pressed"));
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
		
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UKerraAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	UE_LOG(LogTemp, Warning, TEXT("On Abilty Input Released"));
}
