// Fill out your copyright notice in the Description page of Project Settings.


#include "KerraFunctionLibrary.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

UKerraAbilitySystemComponent* UKerraFunctionLibrary::NativeGetKerraASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UKerraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UKerraFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	// Add tag to player character
	UKerraAbilitySystemComponent* ASC = NativeGetKerraASCFromActor(InActor);
	if(!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		// 이 함수를 사용하면 같은 Tag를 여러 번 추가할 수 없다
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UKerraFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	// Remove tag to player character
	UKerraAbilitySystemComponent* ASC = NativeGetKerraASCFromActor(InActor);
	if(ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UKerraFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UKerraAbilitySystemComponent* ASC = NativeGetKerraASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UKerraFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EKerraConfirmType& OutconfirmType)
{
	OutconfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EKerraConfirmType::Yes : EKerraConfirmType::No; 
}
