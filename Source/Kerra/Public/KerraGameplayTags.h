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
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Roll);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Parkour);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SwitchTarget);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Light);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Heavy);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_PickUp);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Quest);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Inventory);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Interaction);
	
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Block);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_TargetLock);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_Rage);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Sample);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_QuickSlot1);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_QuickSlot2);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_QuickSlot3);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_QuickSlot4);
	

	/****** Player Tag ******/
	/* Player Ability Tags */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Sword);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Sword);
	
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Sword);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Sword);
	
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);
	
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Roll);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Parkour);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_TargetLock);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Rage);
	
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Light);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Heavy);
	
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_PickUp_Stones);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Skill_1Skill);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Skill_2Skill);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Skill_3Skill);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Skill_4Skill);
	
	/* Player Cooldown Tags */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Light);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Heavy);

	/* Player Weapon Tags */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);

	/* Player Combat Status Tags */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rolling);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Blocking);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_TargetLock);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Activating);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Active);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Full);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_None);

	/* Player Interaction Tags */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Interaction_None);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Interaction_Quest);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Interaction_Inventory);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Interaction_Dialogue);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Interaction_Storage);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Interaction_PlayCutScene);

	/* Player SetByCaller Tags */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

	/* Player Event Tag */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Sword);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SuccessBlock);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Left);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Right);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ActivateRage);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_AOE);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Consume_Stones);

	/* Enemy Tag */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SummonEnemies);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SpawnStone);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_SummonEnemies);
	
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Unblockable);

	/* Shared Tags */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_SpawnProjectile);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);

	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Invincible);
	
	

	/* Quest Tags */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_ID_1FirstQuest);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_ID_2SecondQeust);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_ID_3ThirdQuest);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_ID_4FirstQuestAfter);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_ID_5SecondQuestAfter);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Quest_ID_6ThirdQuestAfter);

	/* Item Tags */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ID_0None);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ID_1Apple);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ID_2Banana);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_ID_3Orange);

	/* NPC Tag */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(NPC_ID_AAA);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(NPC_ID_BBB);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(NPC_ID_CCC);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(NPC_ID_DDD);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(NPC_ID_EEE);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(NPC_ID_FFF);

	/* Location(Area) Tag */
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Location_ID_Seoul);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Location_ID_Pusan);
	KERRA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Location_ID_Gwangju);
	
}
