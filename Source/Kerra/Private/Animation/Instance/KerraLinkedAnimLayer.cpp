// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Instance/KerraLinkedAnimLayer.h"
#include "Animation/Instance/KerraHeroAnimInstance.h"

UKerraHeroAnimInstance* UKerraLinkedAnimLayer::GetKerraPlayerAnimInstance() const
{
	return Cast<UKerraHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
