// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KerraCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "KerraHero.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UHeroCombatComponent;
class UHeroUIComponent;

UCLASS()
class KERRA_API AKerraHero : public AKerraCharacterBase
{
	GENERATED_BODY()

public:
	AKerraHero();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	FORCEINLINE UHeroCombatComponent* GetKerraPlayerCombatComponent() const { return PlayerCombatComponent; }

	/* Combat Interface */
	virtual UKerraCombatComponent* GetKerraCombatComponent() const override;

	/* UI Interface */
	virtual UKerraUIComponent* GetPawnUIComponent() const override;
	virtual UHeroUIComponent* GetPlayerUIComponent() const override;

private:
	virtual void InitAbilityActorInfo() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UHeroCombatComponent> PlayerCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UHeroUIComponent> UIComponent;

};
