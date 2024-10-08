// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraHeroAbility_Parkour.h"

#include "Character/KerraHero.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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

	
}

void UKerraHeroAbility_Parkour::CalcEssentialValues()
{
	TArray<AActor*> IgnoreToActors;

	// step 1. Check whether exist obstacle or not.
	FVector StartLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	FVector EndLocation = StartLocation + GetAvatarActorFromActorInfo()->GetActorForwardVector() * TraceForwardDistance;
	FHitResult OutHit_CheckForwardObstacle;
	
	bHasObstacle = UKismetSystemLibrary::LineTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation, EndLocation,
		static_cast<ETraceTypeQuery>(ECC_GameTraceChannel1), false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_CheckForwardObstacle, true
	);
	if(!bHasObstacle)
	{
		return;
	}

	// step 2. Measure the depth of the obstacle using a bi-directional trace
	FVector StartLocation_1 = OutHit_CheckForwardObstacle.Location + (OutHit_CheckForwardObstacle.Normal * 20.f);
	FVector EndLocation_1 = StartLocation + ((OutHit_CheckForwardObstacle.Normal * 20.f) + GetAvatarActorFromActorInfo()->GetActorForwardVector() * TraceForwardDistance);
	FHitResult OutHit_ForObstacleDepth_Forward;
	
	UKismetSystemLibrary::LineTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_1, EndLocation_1,
		static_cast<ETraceTypeQuery>(ECC_GameTraceChannel1), false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleDepth_Forward, true
	);

	FVector StartLocation_2 = OutHit_ForObstacleDepth_Forward.TraceEnd;
	FVector EndLocation_2 = StartLocation_2 + (GetAvatarActorFromActorInfo()->GetActorForwardVector() * -TraceForwardDistance);
	FHitResult OutHit_ForObstacleDepth_Backward;
	
	UKismetSystemLibrary::LineTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_2, EndLocation_2,
		static_cast<ETraceTypeQuery>(ECC_GameTraceChannel1), false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleDepth_Backward, true
	);

	// step 3. Measure the height of the obstacle
	FVector StartLocation_3 = OutHit_CheckForwardObstacle.Location + FVector(0.f, 0.f, 100.f);
	FVector EndLocation_3 = OutHit_CheckForwardObstacle.Location + FVector(0.f, 0.f, -100.f);
	FHitResult OutHit_ForObstacleHeight;
	UKismetSystemLibrary::SphereTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_3, EndLocation_3, HeightTraceRadius,
		static_cast<ETraceTypeQuery>(ECC_GameTraceChannel1), false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleHeight, true
	);

	ObstacleDepth =  FMath::Abs((StartLocation_1- OutHit_ForObstacleDepth_Backward.Location).Length());
	ObstacleHeight = OutHit_ForObstacleHeight.ImpactPoint.Z - (GetAvatarActorFromActorInfo()->GetActorLocation().Z - GetKerraPlayerFromActorInfo()->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	UE_LOG(LogTemp, Warning, TEXT("Depth: %f, Height: %f"), ObstacleDepth, ObstacleHeight);
}

void UKerraHeroAbility_Parkour::DetermineParkourMode()
{
	
}
