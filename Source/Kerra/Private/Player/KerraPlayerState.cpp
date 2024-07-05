// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KerraPlayerState.h"

#include "AbilitySystem/KerraAbilitySystemComponent.h"

AKerraPlayerState::AKerraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UKerraAbilitySystemComponent>("AbilitySystemComponent");
}

UAbilitySystemComponent* AKerraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
