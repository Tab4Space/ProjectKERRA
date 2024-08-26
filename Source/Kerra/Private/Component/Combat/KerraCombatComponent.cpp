// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/KerraCombatComponent.h"
#include "Actor/Item/Weapon/KerraWeaponBase.h"

void UKerraCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AKerraWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister)

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if(bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
	UE_LOG(LogTemp, Warning, TEXT("register %s"), *InWeaponTagToRegister.ToString());
}

AKerraWeaponBase* UKerraCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if(CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if(AKerraWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}

AKerraWeaponBase* UKerraCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if(!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;	
	}
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
