// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "Component/Combat/KerraCombatComponent.h"

void UKerraGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if(AbilityActivationPolicy == EKerraAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UKerraGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(AbilityActivationPolicy == EKerraAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UKerraCombatComponent* UKerraGameplayAbility::GetKerraCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UKerraCombatComponent>();
}

UKerraAbilitySystemComponent* UKerraGameplayAbility::GetKerraAbilitySystemComponentFromActorInfo() const
{
	return Cast<UKerraAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
