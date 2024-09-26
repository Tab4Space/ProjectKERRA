// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Instance/KerraCharacterAnimInstance.h"
#include "Character/KerraCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void UKerraCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AKerraCharacterBase>(TryGetPawnOwner());
	if(OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
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
}

void UKerraCharacterAnimInstance::FindLocomotionState()
{
	if( FVector::DotProduct(Velocity.GetSafeNormal(), Acceleration.GetSafeNormal()) < 0.f)
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

void UKerraCharacterAnimInstance::FindLocomotionStartDirection()
{
}

void UKerraCharacterAnimInstance::UpdateOnRunEnter()
{
}

void UKerraCharacterAnimInstance::UpdateOnWalkEnter()
{
}

void UKerraCharacterAnimInstance::UpdateRotationWhileMoving()
{
}

void UKerraCharacterAnimInstance::UpdateLocomotionPlayRate()
{
}
