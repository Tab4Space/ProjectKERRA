// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KerraCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "KerraPlayer.generated.h"


class USpringArmComponent;
class UCameraComponent;

UCLASS()
class KERRA_API AKerraPlayer : public AKerraCharacterBase
{
	GENERATED_BODY()

public:
	AKerraPlayer();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	virtual void InitAbilityActorInfo() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FollowCamera;

};
