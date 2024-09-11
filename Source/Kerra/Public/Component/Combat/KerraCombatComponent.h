// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Component/KerraExtensionComponentBase.h"
#include "KerraCombatComponent.generated.h"


class AKerraWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand,
	TwoHand
};

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

	UFUNCTION(BlueprintCallable, Category="Kerra|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	virtual void ToggleCurrentEquippedWeaponCollision(bool bShouldEnable);
	virtual void ToggleHandCollisionBox(bool bShouldEnable, EToggleDamageType ToggleDamageType);

public:
	/* Track the currently weapon's tag */
	UPROPERTY(BlueprintReadWrite, Category="Kerra|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

protected:
	TArray<AActor*> OverlappedActors;

private:
	TMap<FGameplayTag, AKerraWeaponBase*> CharacterCarriedWeaponMap;
	
};
