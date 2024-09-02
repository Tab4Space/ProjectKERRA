// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraHeroAbility.h"
#include "Character/KerraHero.h"
#include "Player/KerraPlayerController.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "KerraGameplayTags.h"

AKerraHero* UKerraHeroAbility::GetKerraPlayerFromActorInfo()
{
	if(!CachedKerraPlayer.IsValid())
	{
		CachedKerraPlayer = Cast<AKerraHero>(CurrentActorInfo->AvatarActor);
	}
	return CachedKerraPlayer.IsValid() ? CachedKerraPlayer.Get() : nullptr;
}

AKerraPlayerController* UKerraHeroAbility::GetKerraPlayerControllerFromActorInfo()
{
	if(!CachedKerraPlayerController.IsValid())
	{
		CachedKerraPlayerController = Cast<AKerraPlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedKerraPlayerController.IsValid() ? CachedKerraPlayerController.Get() : nullptr;
}

UHeroCombatComponent* UKerraHeroAbility::GetKerraPlayerCombatComponentFromActorInfo()
{
	return GetKerraPlayerFromActorInfo()->GetKerraPlayerCombatComponent();
}

FGameplayEffectSpecHandle UKerraHeroAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
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
