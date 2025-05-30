// Fill out your copyright notice in the Description page of Project Settings.


#include "KerraGameplayTags.h"

namespace KerraGameplayTags
{
	/* Input Tags */
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip, "InputTag.Equip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Unequip, "InputTag.Unequip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Sword, "InputTag.LightAttack.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Sword, "InputTag.HeavyAttack.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "InputTag.Roll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Parkour, "InputTag.Parkour");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "InputTag.SwitchTarget");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SpecialWeaponAbility_Light, "InputTag.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SpecialWeaponAbility_Heavy, "InputTag.SpecialWeaponAbility.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_PickUp, "InputTag.PickUp");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Quest, "InputTag.Quest");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Inventory, "InputTag.Inventory");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interaction, "InputTag.Interaction");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_Block, "InputTag.MustBeHeld.Block");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_Rage, "InputTag.Toggleable.Rage");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_QuickSlot1, "InputTag.QuickSlot1");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_QuickSlot2, "InputTag.QuickSlot2");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_QuickSlot3, "InputTag.QuickSlot3");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_QuickSlot4, "InputTag.QuickSlot4");

	/****** Player Tag ******/
	/* Player Ability Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Sword, "Player.Ability.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Sword, "Player.Ability.Unequip.Sword");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Sword, "Player.Ability.Attack.Light.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Sword, "Player.Ability.Attack.Heavy.Sword");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Roll, "Player.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Parkour, "Player.Ability.Parkour");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block, "Player.Ability.Block");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetLock, "Player.Ability.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Rage, "Player.Ability.Rage");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_SpecialWeaponAbility_Light, "Player.Ability.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_SpecialWeaponAbility_Heavy, "Player.Ability.SpecialWeaponAbility.Heavy");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_PickUp_Stones, "Player.Ability.PickUp.Stones");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_1Skill, "Player.Ability.Skill.1_Skill");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_2Skill, "Player.Ability.Skill.2_Skill");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_3Skill, "Player.Ability.Skill.3_Skill");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_4Skill, "Player.Ability.Skill.4_skill");

	/* Player Cooldown Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_SpecialWeaponAbility_Light, "Player.Cooldown.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_SpecialWeaponAbility_Heavy, "Player.Cooldown.SpecialWeaponAbility.Heavy");

	/* Player Weapon Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");

	/* Player Combat Status Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rolling, "Player.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Blocking, "Player.Status.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_TargetLock, "Player.Status.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_Activating, "Player.Status.Rage.Activating");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_Active, "Player.Status.Rage.Active");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_Full, "Player.Status.Rage.Full");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_None, "Player.Status.Rage.None");

	/* Player Interaction Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Interaction_None, "Player.Status.Interaction.None");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Interaction_Quest, "Player.Status.Interaction.Quest");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Interaction_Inventory, "Player.Status.Interaction.Inventory");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Interaction_Dialogue, "Player.Status.Interaction.Dialogue");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Interaction_Storage, "Player.Status.Interaction.Storage");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Interaction_PlayCutScene, "Player.Status.Interaction.PlayCutScene");

	/* Player SetByCaller Tags */
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy");

	/* Player Event Tag */
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Sword, "Player.Event.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Sword, "Player.Event.Unequip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SuccessBlock, "Player.Event.SuccessBlock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Left, "Player.Event.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Right, "Player.Event.SwitchTarget.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_ActivateRage, "Player.Event.ActivateRage");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_AOE, "Player.Event.AOE");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Consume_Stones, "Player.Event.Consume.Stones");

	/* Enemy Tag */
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_SummonEnemies, "Enemy.Ability.SummonEnemies");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_SpawnStone, "Enemy.Ability.SpawnStone");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_SummonEnemies, "Enemy.Event.SummonEnemies");
	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Unblockable, "Enemy.Status.Unblockable");

	/* Shared Tags */
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Invincible, "Shared.Status.Invincible");

	/* Quest Tags */
	UE_DEFINE_GAMEPLAY_TAG(Quest_ID_1FirstQuest, "Quest.ID.1_FirstQuest");
	UE_DEFINE_GAMEPLAY_TAG(Quest_ID_2SecondQeust, "Quest.ID.2_SecondQuest");
	UE_DEFINE_GAMEPLAY_TAG(Quest_ID_3ThirdQuest, "Quest.ID.3_ThirdQuest");
	UE_DEFINE_GAMEPLAY_TAG(Quest_ID_4FirstQuestAfter, "Quest.ID.4_FirstQuestAfter");
	UE_DEFINE_GAMEPLAY_TAG(Quest_ID_5SecondQuestAfter, "Quest.ID.5_SecondQuestAfter");
	UE_DEFINE_GAMEPLAY_TAG(Quest_ID_6ThirdQuestAfter, "Quest.ID.6_ThirdQuestAfter");

	/* Item Tags */
	UE_DEFINE_GAMEPLAY_TAG(Item_ID_0None, "Item.ID.0_None");
	UE_DEFINE_GAMEPLAY_TAG(Item_ID_1Apple, "Item.ID.1_Apple");
	UE_DEFINE_GAMEPLAY_TAG(Item_ID_2Banana, "Item.ID.2_Banana");
	UE_DEFINE_GAMEPLAY_TAG(Item_ID_3Orange, "Item.ID.3_Orange");

	/* NPC Tag */
	UE_DEFINE_GAMEPLAY_TAG(NPC_ID_AAA, "NPC.ID.AAA");
	UE_DEFINE_GAMEPLAY_TAG(NPC_ID_BBB, "NPC.ID.BBB");
	UE_DEFINE_GAMEPLAY_TAG(NPC_ID_CCC, "NPC.ID.CCC");
	UE_DEFINE_GAMEPLAY_TAG(NPC_ID_DDD, "NPC.ID.DDD");
	UE_DEFINE_GAMEPLAY_TAG(NPC_ID_EEE, "NPC.ID.EEE");
	UE_DEFINE_GAMEPLAY_TAG(NPC_ID_FFF, "NPC.ID.FFF");

	/* Location(Area) Tag */
	UE_DEFINE_GAMEPLAY_TAG(Location_ID_Seoul, "Location.ID.Seoul");
	UE_DEFINE_GAMEPLAY_TAG(Location_ID_Pusan, "Location.ID.Pusan");
	UE_DEFINE_GAMEPLAY_TAG(Location_ID_Gwangju, "Location.ID.Gwangju");
}
