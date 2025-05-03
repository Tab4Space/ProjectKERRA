// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Pickup/KerraStoneBase.h"

#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "Character/KerraHero.h"
#include "KerraGameplayTags.h"

void AKerraStoneBase::Consume(UKerraAbilitySystemComponent* InASC, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();
	InASC->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, InASC->MakeEffectContext());

	

	BP_OnStoneConsumed();
}

void AKerraStoneBase::OnPickUpCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AKerraHero* OverlappedActor = Cast<AKerraHero>(OtherActor))
	{
		Cast<UKerraAbilitySystemComponent>(OverlappedActor->GetAbilitySystemComponent())->TryActivateAbilityByTag(KerraGameplayTags::Player_Ability_PickUp_Stones);
	}
}
