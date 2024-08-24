// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Instance/KerraCharacterAnimInstance.h"

#include "Character/KerraCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	
}
