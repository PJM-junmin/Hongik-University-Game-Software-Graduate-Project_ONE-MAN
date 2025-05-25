// Vince Petrelli all Rights Reserved

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

// Reference https://dev.epicgames.com/community/learning/tutorials/aqrD/unreal-engine-enhanced-input-binding-with-gameplay-tags-c
// Easily to Check a GameObject's State with Tags
namespace OMGameplayTags
{
	// Input Tags
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipSword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnEquipSword);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipGreatSword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnEquipGreatSword);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Sword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Sword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_GreatSword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_GreatSword);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Sprint);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Roll);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SwitchTarget);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Light);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Heavy);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_PickUp_Potions);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Block);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_TargetLock);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_Rage);
	

	// Custom Input Tags
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Spacebar);


	/*************************************
				  Player Tags	
	**************************************/
	// Player Ability Tags
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Sword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_UnEquip_Sword);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_GreatSword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_UnEquip_GreatSword);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Sword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_GreatSword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Sword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_GreatSword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Roll);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Jump);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_TargetLock);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Rage);

	// Player Weapon Ability
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Light);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Heavy);
	
	
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_PickUp_Potions);


	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Light);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Heavy);


	// Player Weapon Tags
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_GreatSword);


	// Player Event Tags
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquip_Sword);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_GreatSword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquip_GreatSword);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SuccessfulBlock);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Sprinting);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Left);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Right);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ActiveRage);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_AOE); // Aera of Effect
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ConsumePotions); 


	// Combo End Attack
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);

	// Rolling & Jumping & Sprinting
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rolling);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Jumping);

	// Block other Attack
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Blocking);

	// Rage
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Activating);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Active);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Full);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_None);

	// TargetLock
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_TargetLock);

	// Player WeaponType Tag
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Weapon);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Weapon_GreatSword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Weapon_Sword);

	// Player AttackType
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

	/*************************************
				  Enemy Tags
	**************************************/
	//EnemyType
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_BossAttack1);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_BossAttack2);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_BossCombo1);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_BossCombo2);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_BackRolling);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SummonEnemies);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SpawnPotion);


	// Enemey Weapon Tags
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_SummonEnemies);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Unblockable);


	/*************************************
				  Shared Tags
	**************************************/
	// Melee Hit
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_SpawnProjectile);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Death);

	// HitReact Direction
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back);
	
	// Invincible
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Invincible);


	/*************************************
				Game Data Tags
	**************************************/
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_SurvivalGameModeMap);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_MainMenuMap);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_SaveGame_Slot_1);

}