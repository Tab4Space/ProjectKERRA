// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/Weapon/KerraWeaponBase.h"
#include "Struct/KerraStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "HeroWeapon.generated.h"



UCLASS()
class KERRA_API AHeroWeapon : public AKerraWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	FKerraPlayerWeaponData KerraPlayerWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
