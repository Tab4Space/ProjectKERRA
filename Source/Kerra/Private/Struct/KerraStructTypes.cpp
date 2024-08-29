// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/KerraStructTypes.h"
#include "AbilitySystem/Abilities/KerraPlayerGameplayAbility.h"

bool FKerraPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
