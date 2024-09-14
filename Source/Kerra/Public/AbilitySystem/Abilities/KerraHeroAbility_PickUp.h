// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KerraHeroAbility.h"
#include "KerraHeroAbility_PickUp.generated.h"


class AKerraStoneBase;

UCLASS()
class KERRA_API UKerraHeroAbility_PickUp : public UKerraHeroAbility
{
	GENERATED_BODY()

protected:
	/* GameplayAbility Interface */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void CollectStones();

	UFUNCTION(BlueprintCallable)
	void ConsumeStones();

private:
	UPROPERTY(EditDefaultsOnly)
	float BoxTraceDistance = 50.f;

	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(100.f);

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> PickUpTraceChannel;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebug = false;

	UPROPERTY()
	TArray<AKerraStoneBase*> CollectedStones;
};
