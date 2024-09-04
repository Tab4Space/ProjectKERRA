// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "KerraGameplayTags.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	// UE_LOG(LogTemp, Warning, TEXT("%s is hitting %s"), *GetOwningPawn()->GetActorNameOrLabel(), *HitActor->GetActorNameOrLabel());

	if(OverlappedActors.Contains(HitActor))
	{
		return;
	}
	OverlappedActors.AddUnique(HitActor);

	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = false;
	const bool bIsMyAttackUnblockable = false;
	
	if(bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		// TODO: check blocking
	}
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	
	if(bIsValidBlock)
	{
		// TODO: success blocking
	}
	else
	{
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), KerraGameplayTags::Shared_Event_MeleeHit, EventData);
	}
}
