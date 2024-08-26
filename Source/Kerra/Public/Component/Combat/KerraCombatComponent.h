// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Component/KerraExtensionComponentBase.h"
#include "KerraCombatComponent.generated.h"


class AKerraWeaponBase;

UCLASS()
class KERRA_API UKerraCombatComponent : public UKerraExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Kerra|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AKerraWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category="Kerra|Combat")
	AKerraWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UFUNCTION(BlueprintCallable, Category="Kerra|Combat")
	AKerraWeaponBase* GetCharacterCurrentEquippedWeapon() const;

public:
	/* Track the currently weapon's tag */
	UPROPERTY(BlueprintReadWrite, Category="Kerra|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

private:
	TMap<FGameplayTag, AKerraWeaponBase*> CharacterCarriedWeaponMap;
	
};
