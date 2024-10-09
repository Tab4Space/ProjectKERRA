// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KerraHeroAbility.h"
#include "Struct/KerraEnumTypes.h"
#include "KerraHeroAbility_Parkour.generated.h"


UCLASS()
class KERRA_API UKerraHeroAbility_Parkour : public UKerraHeroAbility
{
	GENERATED_BODY()

protected:
	/* Interface */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION(BlueprintCallable)
	void CalcDistanceToParkourTarget();

	UFUNCTION(BlueprintCallable)
	void CalcEssentialValues();

	UFUNCTION(BlueprintCallable)
	EKerraParkourType DetermineParkourMode();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Parkour")
	float TraceForwardDistance;

	UPROPERTY(EditDefaultsOnly, Category="Parkour")
	float CapsuleTraceRadius = 42.f;

	UPROPERTY(EditDefaultsOnly, Category="Parkour")
	float CapsuleTraceHalfHeight = 90.f;

	UPROPERTY(EditDefaultsOnly, Category="Parkour")
	float ObstacleHeightThreshold = 250.f;

	UPROPERTY(EditDefaultsOnly, Category="Parkour")
	bool bDrawDebug;

	EKerraParkourType ParkourType = EKerraParkourType::None;

private:
	float ObstacleDepth;
	float ObstacleHeight;

	bool bHasObstacle;
	bool bSuccessParkour = false;;
	float HeightTraceRadius = 30.f;

	FVector ParkourFrontLedgeLocation;
	FVector ParkourBackLedgeLocation;
	FVector ParkourLandLocation;
};
