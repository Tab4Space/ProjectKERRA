// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "KerraGameplayAbility.generated.h"


UENUM(BlueprintType)
enum class EKerraAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class KERRA_API UKerraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	

protected:
	UPROPERTY(EditDefaultsOnly, Category="KerraAbility")
	EKerraAbilityActivationPolicy AbilityActivationPolicy = EKerraAbilityActivationPolicy::OnTriggered;
};
