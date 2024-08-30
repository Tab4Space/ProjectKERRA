// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/KerraCombatComponent.h"
#include "KerraPlayerCombatComponent.generated.h"


class APlayerWeapon;

UCLASS()
class KERRA_API UKerraPlayerCombatComponent : public UKerraCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Kerra|Combat")
	APlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category="Kerra|Combat")
	APlayerWeapon* GetPlayerCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category="Kerra|Combat")
	float GetPlayerCurrentEquippedWeaponDamageAtLevel(int32 InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
