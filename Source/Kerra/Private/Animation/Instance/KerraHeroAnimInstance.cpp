// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Instance/KerraHeroAnimInstance.h"

#include "Character/KerraHero.h"

void UKerraHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(OwningCharacter)
	{
		OwningPlayerCharacter = Cast<AKerraHero>(OwningCharacter);
	}
}

void UKerraHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
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
