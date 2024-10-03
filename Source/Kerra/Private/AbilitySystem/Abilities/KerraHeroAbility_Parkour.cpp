// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraHeroAbility_Parkour.h"

1#include "Kismet/KismetSystemLibrary.h"

void UKerraHeroAbility_Parkour::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UKerraHeroAbility_Parkour::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UKerraHeroAbility_Parkour::CalcDistanceToParkourTarget()
{
	TArray<AActor*> IgnoreToActors;
	FHitResult OutHit;

	FVector StartLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	FVector EndLocation = StartLocation + GetAvatarActorFromActorInfo()->GetActorForwardVector() * TraceForwardDistance;
	
	UKismetSystemLibrary::LineTraceSingle(
		GetAvatarActorFromActorInfo(),
		StartLocation,
		EndLocation,
		static_cast<ETraceTypeQuery>(ECC_GameTraceChannel1),
		false,
		IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		OutHit,
		true
	);
	return;
}
