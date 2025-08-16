// MIT

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace ALSXTGASGameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Effect_NoLevel);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Effect_Type_Cooldown);
	
	namespace CharacterTags
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Type_PC);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Type_NPC);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_State_BlockHealthRegen);
	}

	namespace BasicAttack
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_DamageType_DirectDamage);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Resistance_Modifier_DirectDamage);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Resistance_Ignore_DirectDamage);
	}
	
	namespace State
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Health);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Blood);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_BodyTemp);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Hydration);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Nutrition);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Encumberance);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Energy);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Stamina);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Strength);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Stability);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_HoldBreath);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Health);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Blood);

		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_BodyTemp);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Hydration);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Nutrition);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Encumberance);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Energy);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Stamina);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Strength);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Stability);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_HoldBreath);
	}
	
	namespace Statuses
	{
		
		// Status Example
		// -- Bleeding --
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Debuff_Bleeding);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_DamageType_Bleeding);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Immunity_Bleeding);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Resistance_Modifier_Bleeding);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Resistance_Ignore_Bleeding);
	}

	namespace Movement
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Sprinting);
	}
}