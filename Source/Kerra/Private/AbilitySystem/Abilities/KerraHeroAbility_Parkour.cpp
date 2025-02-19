// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraHeroAbility_Parkour.h"
#include "MotionWarpingComponent.h"
#include "Character/KerraHero.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/KerraCharacterBase.h"

#define ECC_Parkour ECC_GameTraceChannel1


void UKerraHeroAbility_Parkour::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UKerraHeroAbility_Parkour::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UKerraHeroAbility_Parkour::CalcEssentialValues()
{
	TArray<AActor*> IgnoreToActors;
	IgnoreToActors.Add(GetAvatarActorFromActorInfo());

	ETraceTypeQuery ParkourTraceType = UEngineTypes::ConvertToTraceType(ECC_Parkour);

	// step 1. Check whether exist obstacle or not.
	FVector StartLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	FVector EndLocation = StartLocation + GetAvatarActorFromActorInfo()->GetActorForwardVector() * TraceForwardDistance;
	FHitResult OutHit_CheckForwardObstacle;

	bHasObstacle = UKismetSystemLibrary::LineTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation, EndLocation,
		ParkourTraceType, false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_CheckForwardObstacle, true
	);
	if(!bHasObstacle)
	{
		// not exist obstacle, fail parkour
		bSuccessParkour = false;
		return;
	}

	// step 2. Measure the height of the obstacle and set front ledge location
	FVector StartLocation_2 = OutHit_CheckForwardObstacle.Location + FVector(0.f, 0.f, ObstacleHeightThreshold);
	FVector EndLocation_2 = OutHit_CheckForwardObstacle.Location + FVector(0.f, 0.f, -ObstacleHeightThreshold);
	FHitResult OutHit_ForObstacleHeight;
	
	UKismetSystemLibrary::SphereTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_2, EndLocation_2, SphereTraceRadius,
		ParkourTraceType, false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleHeight, true
	);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OutHit_ForObstacleHeight.GetActor()->GetActorNameOrLabel());
	ObstacleHeight = OutHit_ForObstacleHeight.ImpactPoint.Z - (GetAvatarActorFromActorInfo()->GetActorLocation().Z - GetKerraPlayerFromActorInfo()->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	if(ObstacleHeight > ObstacleHeightThreshold)
	{
		// if too high obstacle, fail parkour
		bSuccessParkour = false;
		return;
	}
	bHasFrontLedge = true;
	ParkourFrontLedgeLocation = OutHit_ForObstacleHeight.ImpactPoint + (GetAvatarActorFromActorInfo()->GetActorForwardVector() * 10.f);
	
	// step 3. Check whether exist obstacle or not on the first obstacle.
	FVector StartLocation_3 = OutHit_ForObstacleHeight.Location;
	StartLocation_3.Z += (10.f + CapsuleTraceHalfHeight);
	FVector EndLocation_3 = StartLocation_3 + (GetAvatarActorFromActorInfo()->GetActorForwardVector() * 100.f);
	FHitResult OutHit_ForObstacleUpside;
	
	bHasAnotherObstacle = UKismetSystemLibrary::CapsuleTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_3, EndLocation_3, CapsuleTraceRadius, CapsuleTraceHalfHeight,
		ParkourTraceType, false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleUpside, true 
	);

	if(bHasAnotherObstacle && OutHit_ForObstacleUpside.Distance <= 70.f)
	{
		// check second floor
		bSuccessParkour = false;
		return;
	}

	// if pass to step 3, success parkour
	bSuccessParkour = true;
	
	// step 4. Measure the depth of the obstacle using a bi-directional trace
	FVector StartLocation_4_Forward = OutHit_CheckForwardObstacle.Location + (OutHit_CheckForwardObstacle.Normal * 20.f);
	FVector EndLocation_4_Forward = StartLocation + ((OutHit_CheckForwardObstacle.Normal * 20.f) + GetAvatarActorFromActorInfo()->GetActorForwardVector() * TraceForwardDistance);
	FHitResult OutHit_ForObstacleDepth_Forward;
	
	UKismetSystemLibrary::LineTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_4_Forward, EndLocation_4_Forward,
		ParkourTraceType, false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleDepth_Forward, true
	);

	FVector StartLocation_4_Backward = OutHit_ForObstacleDepth_Forward.TraceEnd;
	FVector EndLocation_4_Backward = StartLocation_4_Backward + (GetAvatarActorFromActorInfo()->GetActorForwardVector() * -TraceForwardDistance);
	FHitResult OutHit_ForObstacleDepth_Backward;
	
	UKismetSystemLibrary::LineTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_4_Backward, EndLocation_4_Backward,
		ParkourTraceType, false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleDepth_Backward, true
	);
	ObstacleDepth =  FMath::Abs((OutHit_ForObstacleDepth_Forward.Location - OutHit_ForObstacleDepth_Backward.Location).Length());
	
	// step 5. Check back ledge location
	FVector StartLocation_5 = OutHit_CheckForwardObstacle.Location + (GetAvatarActorFromActorInfo()->GetActorForwardVector() * ObstacleDepth) + FVector(0.f, 0.f, ObstacleHeightThreshold);
	FVector EndLocation_5 = StartLocation_5 + FVector(0.f, 0.f, -ObstacleHeightThreshold);
	FHitResult OutHit_ForObstacleBackLedge;

	bool Step5_Result = UKismetSystemLibrary::SphereTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_5, EndLocation_5, SphereTraceRadius,
		ParkourTraceType, false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleBackLedge, true
	);

	if(Step5_Result && ObstacleDepth <= 70.f)
	{
		bHasBackLedge = true;
		ParkourBackLedgeLocation = OutHit_ForObstacleBackLedge.ImpactPoint;
	}

	// step 6. Check landing location
	FVector StartLocation_6 = OutHit_CheckForwardObstacle.Location + (GetAvatarActorFromActorInfo()->GetActorForwardVector() * (ObstacleDepth + 100.f));
	StartLocation_6.Z += (ObstacleHeight+50.f);
	FVector EndLocation_6 = StartLocation_6 + FVector(0.f, 0.f, -(ObstacleHeight+100.f));
	FHitResult OutHit_ForObstacleBackSide;
	
	bHasBackFloor = UKismetSystemLibrary::CapsuleTraceSingle(
		GetAvatarActorFromActorInfo(), StartLocation_6, EndLocation_6, CapsuleTraceRadius, CapsuleTraceHalfHeight,
		ParkourTraceType, false, IgnoreToActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, OutHit_ForObstacleBackSide, true 
	);
	
	if(bHasBackFloor)
	{
		ParkourLandLocation = OutHit_ForObstacleBackSide.ImpactPoint;
	}

	if(bDrawDebug)
	{
		UWorld* World = GetWorld();
		if(!ParkourFrontLedgeLocation.IsZero())
		{
			DrawDebugSphere(World, ParkourFrontLedgeLocation, 20.f, 12, FColor::Yellow, false, 5.f, 0, 1.f);	
		}
		if(!ParkourBackLedgeLocation.IsZero())
		{
			DrawDebugSphere(World, ParkourBackLedgeLocation, 20.f, 12, FColor::Blue, false, 5.f, 0, 1.f);	
		}
		if(!ParkourLandLocation.IsZero())
		{
			DrawDebugSphere(World, ParkourLandLocation, 20.f, 12, FColor::White, false, 5.f, 0, 1.f);	
		}
		UE_LOG(LogTemp, Warning, TEXT("Depth: %f, Height: %f"), ObstacleDepth, ObstacleHeight);
	}
}

EKerraParkourType UKerraHeroAbility_Parkour::DetermineParkourMode()
{
	if (!bSuccessParkour)
	{
		ParkourType = EKerraParkourType::None;
		return EKerraParkourType::None;
	}

	if(bHasFrontLedge && bHasBackLedge && !bHasBackFloor && ObstacleDepth < 60.f)
	{
		ParkourType = EKerraParkourType::Vault; 
		return EKerraParkourType::Vault;
	}
	else if(bHasFrontLedge && bHasBackLedge && bHasBackFloor && ObstacleDepth < 60.f)
	{
		ParkourType = EKerraParkourType::Hurdle;
		return EKerraParkourType::Hurdle;
	}
	else if(bHasFrontLedge && ObstacleDepth >= 60.f)
	{
		ParkourType = EKerraParkourType::Mantle;
		return EKerraParkourType::Mantle;
	}
	else
	{
		ParkourType = EKerraParkourType::None;
		return EKerraParkourType::None;
	}
}

void UKerraHeroAbility_Parkour::UpdateMotionWarpingTarget()
{
	UMotionWarpingComponent* MotionWarpingComponent = GetKerraPlayerFromActorInfo()->GetMotionWarpingComponent();
	check(MotionWarpingComponent);

	if (ParkourType == EKerraParkourType::Mantle)
	{
		ParkourFrontLedgeLocation += (GetAvatarActorFromActorInfo()->GetActorForwardVector() * 20.f);
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("FrontLedge"), ParkourFrontLedgeLocation, GetAvatarActorFromActorInfo()->GetActorRotation());
	}
	else
	{
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("FrontLedge"), ParkourFrontLedgeLocation, GetAvatarActorFromActorInfo()->GetActorRotation());
	}
	
	if(ParkourType == EKerraParkourType::Vault || ParkourType == EKerraParkourType::Hurdle)
	{
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("BackLedge"), ParkourBackLedgeLocation, GetAvatarActorFromActorInfo()->GetActorRotation());
	}
	else
	{
		MotionWarpingComponent->RemoveWarpTarget(TEXT("BackLedge"));
	}

	if(ParkourType == EKerraParkourType::Hurdle)
	{
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("BackFloor"), ParkourLandLocation, GetAvatarActorFromActorInfo()->GetActorRotation());
	}
	else
	{
		MotionWarpingComponent->RemoveWarpTarget(TEXT("BackFloor"));
	}

	/*
	UE_LOG(LogTemp, Warning, TEXT("%d"), bHasFrontLedge)
	UE_LOG(LogTemp, Warning, TEXT("%d"), bHasBackLedge)
	UE_LOG(LogTemp, Warning, TEXT("%d"), bHasBackFloor)

	UE_LOG(LogTemp, Warning, TEXT("%s"), *ParkourFrontLedgeLocation.ToString())
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ParkourBackLedgeLocation.ToString())
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ParkourLandLocation.ToString())
	*/
}

void UKerraHeroAbility_Parkour::CleanUp()
{
	ObstacleDepth = 0.f;
	ObstacleHeight = 0.f;
	
	bSuccessParkour = false;
	bHasObstacle = false;
	bHasAnotherObstacle = false;
	bHasFrontLedge = false;
	bHasBackLedge = false;
	bHasBackFloor = false;
	
	ParkourFrontLedgeLocation = FVector::ZeroVector;
	ParkourBackLedgeLocation = FVector::ZeroVector;
	ParkourLandLocation = FVector::ZeroVector;
}
