// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KerraPlayerState.h"

#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystem/KerraAttributeSet.h"

AKerraPlayerState::AKerraPlayerState()
{
	KerraASC = CreateDefaultSubobject<UKerraAbilitySystemComponent>("KerraASC");
	KerraAS = CreateDefaultSubobject<UKerraAttributeSet>("KerraAS");
}

void AKerraPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	checkf(KerraASC, TEXT("Invalid Kerra Ability System Component"));
	checkf(KerraAS, TEXT("Invalid Kerra Attribute Set"));
	// KerraAS->

	const UKerraAttributeSet* as = Cast<UKerraAttributeSet>(KerraASC->GetAttributeSet(UKerraAttributeSet::StaticClass())); 
	KerraASC->GetGameplayAttributeValueChangeDelegate(as->GetCurrentHealthAttribute());//.AddUObject(&AKerraPlayerState::SetSkillPoints, 1);
}

UAbilitySystemComponent* AKerraPlayerState::GetAbilitySystemComponent() const
{
	return KerraASC;
}

void AKerraPlayerState::AddSkillPoints(int32 InSkillPoints)
{
	SkillPoints += InSkillPoints;
	OnSkillPointsChanged.Broadcast(SkillPoints);
}



void AKerraPlayerState::SetSkillPoints(int32 InSkillPoints)
{
	SkillPoints = InSkillPoints;
	OnSkillPointsChanged.Broadcast(SkillPoints);
}
