// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Struct/KerraStructTypes.h"
#include "KerraAbilitySystemComponent.generated.h"


class UKerraGameplayAbility;

UCLASS()
class KERRA_API UKerraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category="Kerra|Ability", meta=(ApplyLevel = "1"))
	void GrantWeaponAbilities(const TArray<FKerraPlayerAbilitySet>& InDefaultWeaponAbilities, const TArray<FKerraPlayerSpecialAbilitySet>& InSpecialWeaponAbilities ,int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category="Kerra|Ability")
	void RemoveGrantedWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category="Kerra|Ability", meta=(ApplyLevel="1"))
	void GrantAbilityWithTags(TSubclassOf<UKerraGameplayAbility> AbilityClass, int32 ApplyLevel, FGameplayTagContainer AddedTags);

	UFUNCTION(BlueprintCallable, Category="Kerra|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);
};
