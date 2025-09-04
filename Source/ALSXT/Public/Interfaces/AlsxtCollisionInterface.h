#pragma once

#include "NativeGameplayTags.h"
#include "Utility/AlsxtStructs.h"
#include "State/AlsxtImpactReactionState.h"
#include "Settings/AlsxtCollisionSettings.h"
#include "State/AlsxtBumpPoseState.h"
#include "State/AlsxtDefensiveModeState.h"
#include "Settings/AlsxtElementalInteractionSettings.h"
#include "AlsxtCollisionInterface.generated.h"

UINTERFACE(Blueprintable)
class UAlsxtCollisionInterface : public UInterface {
	GENERATED_BODY()
};

class ALSXT_API IAlsxtCollisionInterface {
	GENERATED_BODY()

public:

	// Settings
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Settings")
	UAlsxtImpactReactionSettings* SelectImpactReactionSettings();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Settings")
	UAlsxtElementalInteractionSettings* SelectElementalInteractionSettings();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Collision Interface|Conversions")
	void GetFormFromHit(FDoubleHitResult Hit, FGameplayTag& Form);
	
	// Physics
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Physics")
	void GetActorMass(float& Mass);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Physics")
	void GetActorVelocity(FVector& Velocity);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|Physics")
	FAlsxtPhysicalAnimationState GetCharacterPhysicalAnimationState() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|Physics")
	void SetCharacterPhysicalAnimationState(FAlsxtPhysicalAnimationState NewPhysicalAnimationState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|Physics")
	FGameplayTag GetCharacterPhysicalAnimationMode() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|Physics")
	void SetCharacterPhysicalAnimationMode(const FGameplayTag& NewPhysicalAnimationMode, const TArray<FName>& BelowBoneNames);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|Physics")
	void ResetCharacterPhysicalAnimationMode();

	// Defensive Mode

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Defensive Mode")
	bool Blocking();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Defensive Mode")
	void GetActorThreatPoint(FVector& ThreatPoint);

	// Impact Reaction

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|Impact Reaction")
	void AddCollisionImpulse(FVector NewImpulse);

	// UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|Impact Reaction")
	// void AddCollisionForce(FVector NewImpulse) const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Collision Interface|Impact Reaction")
	UPARAM(meta = (Categories = "Als.Impact Form")) FGameplayTag GetCurrentBumpForm();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Impact Reaction")
	FAlsxtImpactReactionState GetImpactReactionState();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Impact Reaction")
	void GetAnticipationInfo(FGameplayTag& Velocity, FGameplayTag& Form, FTransform& AnticipationTransform, FVector& AnticipationPoint);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Collision Interface|Impact Reaction")
	void GetLocationFromBoneName(FName Hit, FGameplayTag& Location);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Impact Reaction")
	void GetActorPhysicsStates(FGameplayTag& PhysicalMaterial, const TArray<FGameplayTag>& PhysicalStates);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Impact Reaction")
	void GetActorPhysicsDamageInfo(FGameplayTag& DamageType, float& PhysicsBaseDamage, float& PhysicsDamageFrequency);

	// Criteria

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanReact();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanClutchImpactPoint();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanGetUp();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanImpactFall();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanAttackFall();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanReceiveImpulse();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanReceiveSpecialAttacks();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanReceiveUniqueAttacks();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanBeGrappled();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanBeThrown();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanBeRagdolled();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanBeTakenDown();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool CanBeKnockedDown();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldSpawnParticleActor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldSpawnParticleActorModeration();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldClutchImpactPoint();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldStabilize();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldImpactFall();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldAttackFall();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldSyncedAttackFall();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldPerformAttackResponse();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldGetUp();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldPerformCrowdNavigationResponse();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldPerformCrowdNavigationReaction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldCrowdNavigationFall();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldPerformImpactResponse();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool ShouldPerformDefensiveReaction();

	// Damage

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool WillDamageKnockDownPlayer(float Damage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Criteria")
	bool WillDamageKillPlayer(float Damage);

	// States

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|State")
	FAlsxtBumpPoseState GetCrowdNavigationPoseState() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|State")
	FAlsxtBumpPoseState GetBumpPoseState();

	// Reaction

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Reactions")
	void BallisticImpact(FDoubleHitResult Hit);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Reactions")
	void BumpReaction(FDoubleHitResult Hit, FGameplayTag Gait, FGameplayTag Side, FGameplayTag Form);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Reactions")
	void CrowdNavigationReaction(FGameplayTag Gait, FDoubleHitResult Hit, FGameplayTag Side, FGameplayTag Form);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Reactions")
	void AnticipationReaction(const FGameplayTag& Velocity, const FGameplayTag& Side, const FGameplayTag& Form, FVector AnticipationPoint);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Reactions")
	void GetImpactFallLocation(FVector& Location, FDoubleHitResult Hit);

	// Events

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|Reactions")
	void OnStaticMeshAttackCollision(FAttackDoubleHitResult Hit);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Events")
	void PerformSurfaceInteraction(const FGameplayTag& PhysicalMaterial);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Events")
	void ActorBumpCollision(FDoubleHitResult Hit);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|Events")
	FAlsxtDamageResult CalculateActualDamage(FAttackDoubleHitResult Hit);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision Interface|Events")
	void OnActorAttackCollision(FAttackDoubleHitResult Hit);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Collision Interface|Events")
	void OnActorImpactCollision(FDoubleHitResult Hit);

};