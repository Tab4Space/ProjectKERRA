// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/HeroCombatComponent.h"
#include "Actor/Item/Weapon/HeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "KerraGameplayTags.h"

AHeroWeapon* UHeroCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AHeroWeapon* UHeroCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
	return Cast<AHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetPlayerCurrentEquippedWeaponDamageAtLevel(int32 InLevel) const
{
	return GetPlayerCurrentEquippedWeapon()->KerraPlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), KerraGameplayTags::Shared_Event_MeleeHit, Data);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), KerraGameplayTags::Player_Event_HitPause, FGameplayEventData());
	
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), KerraGameplayTags::Player_Event_HitPause, FGameplayEventData());
}
