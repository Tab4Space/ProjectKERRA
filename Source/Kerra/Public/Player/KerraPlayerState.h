// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "KerraPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class KERRA_API AKerraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AKerraPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
};
