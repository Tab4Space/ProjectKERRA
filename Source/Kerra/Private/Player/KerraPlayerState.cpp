// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KerraPlayerState.h"

#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystem/KerraAttributeSet.h"

AKerraPlayerState::AKerraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UKerraAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UKerraAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AKerraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
