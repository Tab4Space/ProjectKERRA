// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Instance/KerraLinkedAnimLayer.h"
#include "Animation/Instance/KerraPlayerAnimInstance.h"

UKerraPlayerAnimInstance* UKerraLinkedAnimLayer::GetKerraPlayerAnimInstance() const
{
	return Cast<UKerraPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
