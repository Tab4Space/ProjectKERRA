// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraEnemyAbility.h"
#include "Character/KerraEnemy.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "KerraGameplayTags.h"

AKerraEnemy* UKerraEnemyAbility::GetEnemyActorInfo()
{
	if(!CachedKerraEnemy.IsValid())
	{
		CachedKerraEnemy = Cast<AKerraEnemy>(CurrentActorInfo->AvatarActor);
	}
	return CachedKerraEnemy.IsValid() ? CachedKerraEnemy.Get() : nullptr;
}

UEnemyCombatComponent* UKerraEnemyAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UKerraEnemyAbility::MakeDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageFloat)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetKerraAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	// define damage
	FGameplayEffectSpecHandle EffectSpecHandle = GetKerraAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(KerraGameplayTags::Shared_SetByCaller_BaseDamage, InDamageFloat.GetValueAtLevel(GetAbilityLevel()));

	return EffectSpecHandle;
}
