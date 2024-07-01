// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KerraCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "KerraPlayer.generated.h"


class USpringArmComponent;
class UCameraComponent;

UCLASS()
class KERRA_API AKerraPlayer : public AKerraCharacterBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AKerraPlayer();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FollowCamera;

	
};
