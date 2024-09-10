// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "KerraGameplayTags.h"
#include "KerraFunctionLibrary.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor))
	{
		return;
	}
	OverlappedActors.AddUnique(HitActor);

	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UKerraFunctionLibrary::NativeDoesActorHaveTag(HitActor, KerraGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UKerraFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), KerraGameplayTags::Enemy_Status_Unblockable);
	
	if(bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UKerraFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	
	if(bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, KerraGameplayTags::Player_Event_SuccessBlock, EventData);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), KerraGameplayTags::Shared_Event_MeleeHit, EventData);
	}
}
