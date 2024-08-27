// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/KerraPlayerCombatComponent.h"
#include "Actor/Item/Weapon/PlayerWeapon.h"

APlayerWeapon* UKerraPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<APlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
