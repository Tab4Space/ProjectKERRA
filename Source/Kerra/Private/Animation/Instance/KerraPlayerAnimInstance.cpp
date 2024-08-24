// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Instance/KerraPlayerAnimInstance.h"

#include "Character/KerraPlayer.h"

void UKerraPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(OwningCharacter)
	{
		OwningPlayerCharacter = Cast<AKerraPlayer>(OwningCharacter);
	}
}

void UKerraPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if(bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}
