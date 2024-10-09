// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraHeroAbility_Parkour.h"

#include "Character/KerraHero.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#define ECC_Parkour ECC_GameTraceChannel1


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
		static_cast<ETraceTypeQuery>(ECC_Parkour), false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_CheckForwardObstacle, true
	);
	if(!bHasObstacle)
	{
		// not exist obstacle, fail parkoiur
		bSuccessParkour = false;
		return;
	}

	// step 2. Measure the height of the obstacle
	FVector StartLocation_2 = OutHit_CheckForwardObstacle.Location + FVector(0.f, 0.f, ObstacleHeightThreshold);
	FVector EndLocation_2 = OutHit_CheckForwardObstacle.Location + FVector(0.f, 0.f, -ObstacleHeightThreshold);
	FHitResult OutHit_ForObstacleHeight;
	
	UKismetSystemLibrary::SphereTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_2, EndLocation_2, HeightTraceRadius,
		static_cast<ETraceTypeQuery>(ECC_Parkour), false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleHeight, true
	);
	ObstacleHeight = OutHit_ForObstacleHeight.ImpactPoint.Z - (GetAvatarActorFromActorInfo()->GetActorLocation().Z - GetKerraPlayerFromActorInfo()->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	if(ObstacleHeight > ObstacleHeightThreshold)
	{
		// if too high obstacle, fail parkour
		bSuccessParkour = false;
		return;
	}
	ParkourFrontLedgeLocation = OutHit_ForObstacleHeight.ImpactPoint;

	// step 3. Measure the depth of the obstacle using a bi-directional trace
	FVector StartLocation_3_Forward = OutHit_CheckForwardObstacle.Location + (OutHit_CheckForwardObstacle.Normal * 20.f);
	FVector EndLocation_3_Forward = StartLocation + ((OutHit_CheckForwardObstacle.Normal * 20.f) + GetAvatarActorFromActorInfo()->GetActorForwardVector() * TraceForwardDistance);
	FHitResult OutHit_ForObstacleDepth_Forward;
	
	UKismetSystemLibrary::LineTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_3_Forward, EndLocation_3_Forward,
		static_cast<ETraceTypeQuery>(ECC_Parkour), false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleDepth_Forward, true
	);

	FVector StartLocation_3_Backward = OutHit_ForObstacleDepth_Forward.TraceEnd;
	FVector EndLocation_3_Backward = StartLocation_3_Backward + (GetAvatarActorFromActorInfo()->GetActorForwardVector() * -TraceForwardDistance);
	FHitResult OutHit_ForObstacleDepth_Backward;
	
	UKismetSystemLibrary::LineTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_3_Backward, EndLocation_3_Backward,
		static_cast<ETraceTypeQuery>(ECC_Parkour), false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleDepth_Backward, true
	);
	ObstacleDepth =  FMath::Abs((OutHit_ForObstacleDepth_Forward.Location - OutHit_ForObstacleDepth_Backward.Location).Length());

	// step 4. Check whether exist obstacle or not on first obstacle.
	FVector StartLocation_4 = (OutHit_CheckForwardObstacle.Location + OutHit_CheckForwardObstacle.Normal*(CapsuleTraceRadius+5.f));
	StartLocation_4.Z = ObstacleHeight + CapsuleTraceHalfHeight + 10.f;
	FVector EndLocation_4 = StartLocation_4 + (GetAvatarActorFromActorInfo()->GetActorForwardVector() * (ObstacleDepth + CapsuleTraceRadius * 2.f + 100.f));
	FHitResult OutHit_ForObstacleUpside;
	
	bool bHasAnotherObstacle = UKismetSystemLibrary::CapsuleTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_4, EndLocation_4, CapsuleTraceRadius, CapsuleTraceHalfHeight,
		static_cast<ETraceTypeQuery>(ECC_Parkour), false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleUpside, true 
	);

	// step 5. Check landing location
	FVector StartLocation_5 = EndLocation_4;
	FVector EndLocation_5 = StartLocation_5 + FVector(0.f, 0.f, -(ObstacleHeight+50.f));
	FHitResult OutHit_ForObstacleBackSide;
	
	bool bLandingHitResult = UKismetSystemLibrary::CapsuleTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_5, EndLocation_5, CapsuleTraceRadius, CapsuleTraceHalfHeight,
		static_cast<ETraceTypeQuery>(ECC_Parkour), false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleBackSide, true 
	);

	if(bLandingHitResult)
	{
		ParkourLandLocation = OutHit_ForObstacleBackSide.ImpactPoint;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Depth: %f, Height: %f"), ObstacleDepth, ObstacleHeight);
}

EKerraParkourType UKerraHeroAbility_Parkour::DetermineParkourMode()
{
	if (!bSuccessParkour)
	{
		return EKerraParkourType::None;
	}

	return EKerraParkourType::None;
}
