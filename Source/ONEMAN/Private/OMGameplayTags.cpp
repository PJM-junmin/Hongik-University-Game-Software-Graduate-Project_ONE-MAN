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

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, "InputTag.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "InputTag.Roll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "InputTag.SwitchTarget");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SpecialWeaponAbility_Light, "InputTag.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SpecialWeaponAbility_Heavy, "InputTag.SpecialWeaponAbility.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_PickUp_Potions, "InputTag.PickUp.Potions");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_Block, "InputTag.MustBeHeld.Block");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_Rage, "InputTag.Toggleable.Rage");


	// Custom Input Tags
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Spacebar, "InputTag.Spacebar");


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

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Roll, "Player.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Jump, "Player.Ability.Jump");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block, "Player.Ability.Block");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetLock, "Player.Ability.TargetLock");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Rage, "Player.Ability.Rage");

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_SpecialWeaponAbility_Light, "Player.Ability.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_SpecialWeaponAbility_Heavy, "Player.Ability.SpecialWeaponAbility.Heavy");
	
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_PickUp_Potions, "Player.Ability.PickUp.Potions");


	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_SpecialWeaponAbility_Light, "Player.Cooldown.SpecialWeaponAbility.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_SpecialWeaponAbility_Heavy, "Player.Cooldown.SpecialWeaponAbility.Heavy");


	// Player Weapon Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_GreatSword, "Player.Weapon.GreatSword");


	// Player Event Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Sword, "Player.Event.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_Sword, "Player.Event.UnEquip.Sword");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_GreatSword, "Player.Event.Equip.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_GreatSword, "Player.Event.UnEquip.GreatSword");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SuccessfulBlock, "Player.Event.SuccessfulBlock");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Sprinting, "Player.Event.Sprinting");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Left, "Player.Event.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Right, "Player.Event.SwitchTarget.Right");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_ActiveRage, "Player.Event.ActiveRage");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_AOE, "Player.Event.AOE"); // Aera of Effect
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_ConsumePotions, "Player.Event.ConsumePotions");


	// Combo End Attack
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher");

	// Rolling & Jumping & Sprinting
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rolling, "Player.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Jumping, "Player.Status.Jumping");

	// Block other Attack 
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Blocking, "Player.Status.Blocking");

	// TargetLock
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_TargetLock, "Player.Status.TargetLock");

	// Rage
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_Activating, "Player.Status.Rage.Activating");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_Active, "Player.Status.Rage.Active");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_Full, "Player.Status.Rage.Full");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rage_None, "Player.Status.Rage.None");

	// Player WeaponType Tag
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Weapon, "Player.Status.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Weapon_GreatSword, "Player.Status.Weapon.GreatSword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Weapon_Sword, "Player.Status.Weapon.Sword");

	// Player AttackType
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy");


	/*************************************
				  Enemy Tags
	**************************************/
	//EnemyType
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_BossAttack1, "Enemy.Ability.Melee.BossAttack1");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_BossAttack2, "Enemy.Ability.Melee.BossAttack2");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_BossCombo1, "Enemy.Ability.Melee.BossCombo1");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_BossCombo2, "Enemy.Ability.Melee.BossCombo2");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_BackRolling, "Enemy.Ability.Melee.BackRolling");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_SummonEnemies, "Enemy.Ability.SummonEnemies");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_SpawnPotion, "Enemy.Ability.SpawnPotion");


	// Player Weapon Tags
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_SummonEnemies, "Enemy.Event.SummonEnemies");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Unblockable, "Enemy.Status.Unblockable");


	/*************************************
				  Shared Tags
	**************************************/
	// Melee Hit
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");

	// HitReact Direction
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");

	// Invincible
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Invincible, "Shared.Status.Invincible");


	/*************************************
				 Game Data Tags
	**************************************/
	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_SurvivalGameModeMap, "GameData.Level.SurvivalGameModeMap");
	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_MainMenuMap, "GameData.Level.MainMenuMap");

	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_1, "GameData.SaveGame.Slot.1");

}