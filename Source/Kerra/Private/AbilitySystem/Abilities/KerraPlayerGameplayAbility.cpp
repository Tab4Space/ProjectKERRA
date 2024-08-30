// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraPlayerGameplayAbility.h"
#include "Character/KerraPlayer.h"
#include "Player/KerraPlayerController.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "KerraGameplayTags.h"

AKerraPlayer* UKerraPlayerGameplayAbility::GetKerraPlayerFromActorInfo()
{
	if(!CachedKerraPlayer.IsValid())
	{
		CachedKerraPlayer = Cast<AKerraPlayer>(CurrentActorInfo->AvatarActor);
	}
	return CachedKerraPlayer.IsValid() ? CachedKerraPlayer.Get() : nullptr;
}

AKerraPlayerController* UKerraPlayerGameplayAbility::GetKerraPlayerControllerFromActorInfo()
{
	if(!CachedKerraPlayerController.IsValid())
	{
		CachedKerraPlayerController = Cast<AKerraPlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedKerraPlayerController.IsValid() ? CachedKerraPlayerController.Get() : nullptr;
}

UKerraPlayerCombatComponent* UKerraPlayerGameplayAbility::GetKerraPlayerCombatComponentFromActorInfo()
{
	return GetKerraPlayerFromActorInfo()->GetKerraPlayerCombatComponent();
}

FGameplayEffectSpecHandle UKerraPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetKerraAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	
	FGameplayEffectSpecHandle EffectSpecHandle = GetKerraAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(KerraGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

	if(InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}
	
	return EffectSpecHandle;
}
