// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/KerraStructTypes.h"
#include "AbilitySystem/Abilities/KerraHeroAbility.h"

bool FKerraPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
