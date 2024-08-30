// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/KerraPlayerCombatComponent.h"
#include "Actor/Item/Weapon/PlayerWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "KerraGameplayTags.h"

APlayerWeapon* UKerraPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<APlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UKerraPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), KerraGameplayTags::Shared_Event_MeleeHit, Data);
	
}

void UKerraPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	
	
}
