// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KerraCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "KerraPlayer.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UKerraPlayerCombatComponent;

UCLASS()
class KERRA_API AKerraPlayer : public AKerraCharacterBase
{
	GENERATED_BODY()

public:
	AKerraPlayer();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	FORCEINLINE UKerraPlayerCombatComponent* GetKerraPlayerCombatComponent() const { return PlayerCombatComponent; }

	/* Combat Interface */
	virtual UKerraCombatComponent* GetKerraCombatComponent() const override;
	/* Combat Interface */

private:
	virtual void InitAbilityActorInfo() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UKerraPlayerCombatComponent> PlayerCombatComponent;

};
