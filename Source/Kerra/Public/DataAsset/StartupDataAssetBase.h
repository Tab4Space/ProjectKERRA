// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StartupDataAssetBase.generated.h"


class UKerraGameplayAbility;
class UKerraAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class KERRA_API UStartupDataAssetBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UKerraAbilitySystemComponent* InASC, int32 InApplyLevel = 1);

protected:
	void GrantAbilities(const TArray<TSubclassOf<UKerraGameplayAbility>>& InAbilitiesToGive, UKerraAbilitySystemComponent* InASC, int32 InApplyLevel = 1);
	

protected:
	/* Ability를 부여받은 직후 활성화해야 하는 것들 */
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UKerraGameplayAbility>> ActivateOnGivenAbilities;

	/* 특정 조건에서 활성회하는 Ability들 */
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UKerraGameplayAbility>> ReactiveAbilities;

	/* 시작할 때 적용되는 Gameplay Effects */
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;
};
