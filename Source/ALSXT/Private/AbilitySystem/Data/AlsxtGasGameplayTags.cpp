// MIT

#include "AbilitySystem/Data/AlsxtGasGameplayTags.h"
#include "NativeGameplayTags.h"

namespace ALSXTAbilityGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Sprint, TEXT("Gameplay.Ability.Sprint"))
	UE_DEFINE_GAMEPLAY_TAG(Breathing, TEXT("Gameplay.Ability.Breathing"))
	UE_DEFINE_GAMEPLAY_TAG(Jump, TEXT("Gameplay.Ability.Jump"))
	UE_DEFINE_GAMEPLAY_TAG(Roll, TEXT("Gameplay.Ability.Roll"))
	UE_DEFINE_GAMEPLAY_TAG(Mantle, TEXT("Gameplay.Ability.Mantle"))
	UE_DEFINE_GAMEPLAY_TAG(HoldItem, TEXT("Gameplay.Ability.HoldItem"))
}

namespace ALSXTGASGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_NoLevel, "Effect.NoLevel", "This GE won't be leveled up or down. Base level will always be the same (upon granting it).")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_Type_Cooldown, "Effect.Type.Cooldown", "This is a cooldown GE")
	
	namespace CharacterTags
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Character_Type_PC, "Character.Type.PlayerCharacter", "A Gameplay Tag applied to Characters that are controlled by a local player.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Character_Type_NPC, "Character.Type.NonPlayerCharacter", "A Gameplay Tag applied to Characters that are AI controlled.")
	}

	namespace StaminaCost
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_StaminaCost_Infinite_Sprint, "StaminaCost.Infinite.Sprint", "A Gameplay Tag applied to Sprinting Stamina Cost")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_StaminaCost_Instant_Jump, "StaminaCost.Instant.Jump", "A Gameplay Tag applied to Jumping Stamina Cost")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_StaminaCost_Instant_Roll, "StaminaCost.Instant.Sprint", "A Gameplay Tag applied to Sprinting Stamina Cost")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_StaminaCost_Instant_Mantle, "StaminaCost.Instant.Mantle", "A Gameplay Tag applied to Mantle Stamina Cost")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_StaminaCost_Instant_Vault, "StaminaCost.Instant.Vault", "A Gameplay Tag applied to Vaulting Stamina Cost")
	}

	namespace Data
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Data_Magnitude_Sprint, "Data.Magnitude.Sprint", "A Gameplay Tag applied to Sprinting Magnitude")
	}

	namespace BasicAttack
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_DamageType_DirectDamage, "DamageType.DirectDamage", "Basic Damage Type. Used to calculated Resistance to Basic Damage.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Resistance_Modifier_DirectDamage, "Resistance.Modifier.DirectDamage", "Granting Resistance to basic Damage")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Resistance_Ignore_DirectDamage, "Resistance.Ignore.DirectDamage", "Ignore Resistance to basic Damage. Will deal true damage.")
	}

	namespace State
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_KnockedDown, "State.KnockedDown", "KnockedDown")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Unconscious, "State.Unconscious", "Unconscious")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Dead, "Gameplay.State.Dead", "Dead")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_HoldingBreath, "State.HoldingBreath", "HoldingBreath Active")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_OutOfBreath, "State.OutOfBreath", "OutOfBreath")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Exhausted, "State.Exhausted", "Exhausted")

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Health, "State.Max.Health", "Max Health reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Stamina, "State.Max.Stamina", "Max Stamina reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Strength, "State.Max.Strength", "Max Strength reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Stability, "State.Max.Stamina", "Max Stamina reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_HoldingBreath, "Gameplay.State.Max.HoldingBreath", "Max HoldingBreath reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Breath, "Gameplay.State.Max.Breath", "Max Breath reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_BreathRegen, "Gameplay.State.Max.BreathRegen", "Max Breath reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_HoldingBreathRegen, "Gameplay.State.Max.HoldingBreathRegen", "Max Breath reached")

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Blood, "State.Max.Blood", "Max Blood reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_BodyTemp, "State.Max.BodyTemp", "Max BodyTemp reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Energy, "State.Max.Energy", "Max Energy reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Hydration, "State.Max.Hydration", "Max Hydration reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Nutrition, "State.Max.Nutrition", "Max Nutrition reached")
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Health, "State.Blocked.Regeneration.Health", "Block Health regeneration.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Stamina, "State.Blocked.Regeneration.Stamina", "Block Stamina regeneration.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Strength, "State.Blocked.Regeneration.Strength", "Block Strength regeneration.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Stability, "State.Blocked.Regeneration.Stability", "Block Stability regeneration.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_HoldBreath, "Gameplay.State.Blocked.Regeneration.HoldingBreath", "Block HoldingBreath regeneration.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Breath, "Gameplay.State.Blocked.Regeneration.Breath", "Block Breath regeneration.")

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Blood, "State.Blocked.Regeneration.Blood", "Block Blood regeneration.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_BodyTemp, "State.Blocked.Regeneration.BodyTemp", "Block BodyTemp regeneration.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Energy, "State.Blocked.Regeneration.Energy", "Block Energy regeneration.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Hydration, "State.Blocked.Regeneration.Hydration", "Block Hydration regeneration.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Nutrition, "State.Blocked.Regeneration.Nutrition", "Block Nutrition regeneration.")
	}
	
	namespace Statuses
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Bleeding, "Debuff.Bleeding", "Is Bleeding. Can be used to trigger more effects.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_DamageType_Bleeding, "DamageType.Bleeding", "Bleeding Damage Type. Used to calculated Resistance to Bleeding Damage.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Immunity_Bleeding, "Immunity.Bleeding", "Immune to Bleeding")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Resistance_Modifier_Bleeding, "Resistance.Modifier.Bleeding", "Granting Resistance to Bleeding")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Resistance_Ignore_Bleeding, "Resistance.Ignore.Bleeding", "Ignore Resistance to Bleeding. Will increase bleeding with the source value.")
	}
	
	namespace Statuses
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Movement_Sprinting, "State.Movement.Sprinting", "Owned when user Sprints")
	}
}