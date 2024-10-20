// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Instance/KerraCharacterAnimInstance.h"

#include "AbilitySystemComponent.h"
#include "Character/KerraCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AnimCharacterMovementLibrary.h"
#include "KerraGameplayTags.h"

void UKerraCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AKerraCharacterBase>(TryGetPawnOwner());
	if(OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
		PrimaryRotation = OwningCharacter->GetActorRotation();
	}
}

void UKerraCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if(!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	/* Update Essential Locomotion Data*/
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	Velocity = OwningCharacter->GetVelocity();
	Acceleration = OwningMovementComponent->GetCurrentAcceleration();
	LastInputVector = OwningMovementComponent->GetLastInputVector();

	if(LocomotionState == EKerraLocomotionState::Idle)
	{
		DistanceToMatch = GetPredictStopDistance();
	}
	else
	{
		DistanceToMatch = 0.f;
	}
}


void UKerraCharacterAnimInstance::NativePostEvaluateAnimation()
{
	if(LocomotionState == EKerraLocomotionState::Idle)
	{
		// TODO: Turn in place
	}
	else
	{
		// TODO: Check gameplay tag list -> movement(rolling, parkour and so on.)
		if(OwningCharacter->GetAbilitySystemComponent()->HasMatchingGameplayTag(KerraGameplayTags::Player_Status_Rolling))
		{
			UE_LOG(LogTemp, Warning, TEXT("Rolling"))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Update Rotation While Moving"));
			UpdateRotationWhileMoving(RotationCurveName);	
		}
	}
}


void UKerraCharacterAnimInstance::FindLocomotionState()
{
	if( FVector::DotProduct(Velocity.GetSafeNormal(), Acceleration.GetSafeNormal()) < -0.5f)
	{
		LocomotionState = EKerraLocomotionState::Idle;
	}
	else if(GroundSpeed > 1.f && Acceleration.Length() > 400.f && OwningMovementComponent->MaxWalkSpeed > 250.f)
	{
		LocomotionState = EKerraLocomotionState::Run;
	}
	else if(GroundSpeed > 1.f && Acceleration.Length() > 0.01f && OwningMovementComponent->MaxWalkSpeed > 1.f)
	{
		LocomotionState = EKerraLocomotionState::Walk;
	}
	else
	{
		LocomotionState = EKerraLocomotionState::Idle;
	}
}

void UKerraCharacterAnimInstance::FindLocomotionStartDirection(const float StartAngle)
{
	if(UKismetMathLibrary::InRange_FloatFloat(StartAngle, -60.f, 60.f))
	{
		MovementDirection = EKerraMovementStartDirection::Forward;
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(StartAngle, 60.f, 120.f))
	{
		MovementDirection = EKerraMovementStartDirection::Right;
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(StartAngle, -120.f, -60.f))
	{
		MovementDirection = EKerraMovementStartDirection::Left;
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(StartAngle, 120.f, 180.f))
	{
		MovementDirection = EKerraMovementStartDirection::BackRight;
	}
	else
	{
		MovementDirection = EKerraMovementStartDirection::BackLeft;
	}
}

void UKerraCharacterAnimInstance::UpdateOnRunEnter()
{
	if(!OwningCharacter)
	{
		return;
	}
	
	StartRotation = OwningCharacter->GetActorRotation();
	PrimaryRotation = LastInputVector.ToOrientationRotator();
	SecondaryRotation = PrimaryRotation;
	LocomotionStartAngle = UKismetMathLibrary::NormalizedDeltaRotator(PrimaryRotation, StartRotation).Yaw;
	FindLocomotionStartDirection(LocomotionStartAngle);
}

void UKerraCharacterAnimInstance::UpdateOnWalkEnter()
{
	if(!OwningCharacter)
	{
		return;
	}
	
	StartRotation = OwningCharacter->GetActorRotation();
	PrimaryRotation = LastInputVector.ToOrientationRotator();
	SecondaryRotation = PrimaryRotation;
	LocomotionStartAngle = UKismetMathLibrary::NormalizedDeltaRotator(PrimaryRotation, StartRotation).Yaw;
	FindLocomotionStartDirection(LocomotionStartAngle);
}

void UKerraCharacterAnimInstance::UpdateRotationWhileMoving(FName CurveName)
{
	PrimaryRotation = UKismetMathLibrary::RInterpTo_Constant(PrimaryRotation, UKismetMathLibrary::MakeRotFromX(LastInputVector), UGameplayStatics::GetWorldDeltaSeconds(this), 1000.f);
	SecondaryRotation = UKismetMathLibrary::RInterpTo(SecondaryRotation, PrimaryRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 8.f);

	FRotator UpdateRotation = FRotator::ZeroRotator;
	float CurveValue = GetCurveValue(CurveName);
	float ArrangeCurveValue = UKismetMathLibrary::MapRangeClamped(CurveValue, 0.f, 1.f, 1.f, 0.f);
	UpdateRotation.Yaw = (ArrangeCurveValue * -1.f * LocomotionStartAngle) + SecondaryRotation.Yaw;
	OwningCharacter->SetActorRotation(UpdateRotation);
}

void UKerraCharacterAnimInstance::UpdateLocomotionPlayRate(FName CurveName, float MinRate, float MaxRate)
{
	float CurveValue = GetCurveValue(CurveName);
	AnimPlayRate = FMath::Clamp(UKismetMathLibrary::SafeDivide(GroundSpeed, CurveValue), MinRate, MaxRate);
}

float UKerraCharacterAnimInstance::GetPredictStopDistance()
{
	FVector PredictVector = UAnimCharacterMovementLibrary::PredictGroundMovementStopLocation(
		Velocity,
		OwningMovementComponent->bUseSeparateBrakingFriction,
		OwningMovementComponent->BrakingFriction,
		OwningMovementComponent->GroundFriction,
		OwningMovementComponent->BrakingFrictionFactor,
		OwningMovementComponent->BrakingDecelerationWalking
	);

	return PredictVector.Length();
}
