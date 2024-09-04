// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Instance/KerraAnimInstanceBase.h"
#include "KerraFunctionLibrary.h"

bool UKerraAnimInstanceBase::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if(APawn* OwningPawn = TryGetPawnOwner())
	{
		return UKerraFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
