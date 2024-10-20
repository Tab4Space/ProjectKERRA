// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Instance/KerraAnimInstanceBase.h"
#include "KerraFunctionLibrary.h"

bool UKerraAnimInstanceBase::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	APawn* OwningPawn = TryGetPawnOwner();
	
	if(OwningPawn != nullptr)
	{
		return UKerraFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
