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


	// Player Weapon Tags
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_GreatSword);


	// Player Event Tags
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquip_Sword);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_GreatSword);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquip_GreatSword);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);

	// Combo End Attack
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);

	// Player AttackType
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

	/*************************************
				  Enemy Tags
	**************************************/
	//EnemyType
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);

	// Enemey Weapon Tags
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);


	/*************************************
				  Shared Tags
	**************************************/
	// Melee Hit
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);


	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);

	ONEMAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Death);


}
