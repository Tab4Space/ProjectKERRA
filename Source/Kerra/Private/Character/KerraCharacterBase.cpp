// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KerraCharacterBase.h"


AKerraCharacterBase::AKerraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
}

UAbilitySystemComponent* AKerraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


UKerraCombatComponent* AKerraCharacterBase::GetKerraCombatComponent() const
{
	return nullptr;
}

UKerraUIComponent* AKerraCharacterBase::GetPawnUIComponent() const
{
	return nullptr;
}

void AKerraCharacterBase::InitAbilityActorInfo()
{
}

void AKerraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
