// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KerraHeroAbility.h"
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
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Parkour")
	float TraceForwardDistance;

	UPROPERTY(EditDefaultsOnly, Category="Parkour")
	bool bDrawDebug;

private:
	float WallThickness;
};
