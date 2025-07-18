// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KerraGameplayAbility.h"
#include "KerraHeroAbility.generated.h"


class UKerraAttributeSet;
class AKerraPlayerState;
class UHeroUIComponent;
class AKerraHero;
class AKerraPlayerController;
class UHeroCombatComponent;

UCLASS()
class KERRA_API UKerraHeroAbility : public UKerraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	AKerraHero* GetKerraPlayerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	AKerraPlayerController* GetKerraPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	AKerraPlayerState* GetKerraPlayerState();

	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	UKerraAbilitySystemComponent* GetKerraAbilitySystemComponent();
	
	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	UKerraAttributeSet* GetKerraAttributeSet();

	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	UHeroCombatComponent* GetKerraPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	FGameplayEffectSpecHandle MakeDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

	UFUNCTION(BlueprintCallable, Category="Kerra|Ability")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime);
	
	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	UHeroUIComponent* GetHeroUIComponentFromActorInfo();

private:
	// 원시 포인터와는 다르게 object를 활성 상태로 유지하지 않는다, 단순히 참조만 보유하고 있다
	// 참조만 보유하되 레퍼런스 카운팅을 증가시키고 싶지 않을 때 사용한다
	TWeakObjectPtr<AKerraHero> CachedKerraPlayer;
	TWeakObjectPtr<AKerraPlayerController> CachedKerraPC;
	TWeakObjectPtr<AKerraPlayerState> CachedKerraPS;
	TWeakObjectPtr<UKerraAbilitySystemComponent> CachedKerraASC;
	TWeakObjectPtr<UKerraAttributeSet> CachedKerraAS;
};
