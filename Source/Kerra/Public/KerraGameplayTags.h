// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace KerraGameplayTags
{
	/* Input Tags */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Equip);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Unequip);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Sword);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Sword);

	/* Player Tag */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Sword);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Sword);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Sword);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Sword);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);

	/* Player Event Tag */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Sword);

	/* Enemy Tag */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);
}
