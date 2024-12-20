// Vince Petrelli all Rights Reserved


#include "OMGameplayTags.h"

namespace OMGameplayTags
{
	// Input Tags
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipSword, "InputTag.EquipSword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquipSword, "InputTag.UnEquipSword");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipGreatSword, "InputTag.EquipGreatSword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquipGreatSword, "InputTag.UnEquipGreatSword");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Sword, "InputTag.LightAttack.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Sword, "InputTag.HeavyAttack.Sword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_GreatSword, "InputTag.LightAttack.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_GreatSword, "InputTag.HeavyAttack.GreatSword");


	/*************************************
				  Player Tags
	**************************************/
	// Player Ability Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Sword, "Player.Ability.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_UnEquip_Sword, "Player.Ability.UnEquip.Sword");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_GreatSword, "Player.Ability.Equip.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_UnEquip_GreatSword, "Player.Ability.UnEquip.GreatSword");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Sword, "Player.Ability.Attack.Light.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_GreatSword, "Player.Ability.Attack.Light.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Sword, "Player.Ability.Attack.Heavy.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_GreatSword, "Player.Ability.Attack.Heavy.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause");


	// Player Weapon Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_GreatSword, "Player.Weapon.GreatSword");


	// Player Event Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Sword, "Player.Event.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_Sword, "Player.Event.UnEquip.Sword");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_GreatSword, "Player.Event.Equip.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_GreatSword, "Player.Event.UnEquip.GreatSword");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");

	// Combo End Attack
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher");

	// Player AttackType
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy");


	/*************************************
				  Enemy Tags
	**************************************/
	//EnemyType
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");

	// Player Weapon Tags
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");


	/*************************************
				  Shared Tags
	**************************************/
	// Melee Hit
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");
}