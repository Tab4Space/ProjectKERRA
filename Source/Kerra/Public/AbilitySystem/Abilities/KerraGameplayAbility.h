// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Struct/KerraEnumTypes.h"
#include "KerraGameplayAbility.generated.h"


class UKerraCombatComponent;
class UKerraAbilitySystemComponent;

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
	// Called when call in 'GiveAbility()' 
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	UKerraCombatComponent* GetKerraCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	UKerraAbilitySystemComponent* GetKerraAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category="Kerra|Ability", meta=(DisplayName="Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs="OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EKerraSuccessType& OutSuccessType);

	UFUNCTION(BlueprintCallable, Category="Kerra|Ability")
	void ApplyGameplaySpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle, const TArray<FHitResult>& HitResults);

protected:
	UPROPERTY(EditDefaultsOnly, Category="KerraAbility")
	EKerraAbilityActivationPolicy AbilityActivationPolicy = EKerraAbilityActivationPolicy::OnTriggered;
};
