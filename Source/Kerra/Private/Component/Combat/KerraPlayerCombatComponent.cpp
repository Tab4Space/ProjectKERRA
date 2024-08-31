// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/KerraPlayerCombatComponent.h"
#include "Actor/Item/Weapon/PlayerWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "KerraGameplayTags.h"

APlayerWeapon* UKerraPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<APlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

APlayerWeapon* UKerraPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
	return Cast<APlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UKerraPlayerCombatComponent::GetPlayerCurrentEquippedWeaponDamageAtLevel(int32 InLevel) const
{
	return GetPlayerCurrentEquippedWeapon()->KerraPlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UKerraPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
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

void UKerraPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), KerraGameplayTags::Player_Event_HitPause, FGameplayEventData());
}
