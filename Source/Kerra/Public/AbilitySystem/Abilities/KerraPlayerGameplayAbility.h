// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KerraGameplayAbility.h"
#include "KerraPlayerGameplayAbility.generated.h"


class AKerraPlayer;
class AKerraPlayerController;
class UKerraPlayerCombatComponent;

UCLASS()
class KERRA_API UKerraPlayerGameplayAbility : public UKerraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	AKerraPlayer* GetKerraPlayerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	AKerraPlayerController* GetKerraPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Kerra|Ability")
	UKerraPlayerCombatComponent* GetKerraPlayerCombatComponentFromActorInfo();

private:
	// 원시 포인터와는 다르게 object를 활성 상태로 유지하지 않는다, 단순히 참조만 보유하고 있다
	// 참조만 보유하되 레퍼런스 카운팅을 증가시키고 싶지 않을 때 사용한다
	TWeakObjectPtr<AKerraPlayer> CachedKerraPlayer;
	TWeakObjectPtr<AKerraPlayerController> CachedKerraPlayerController;
};
