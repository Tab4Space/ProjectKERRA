// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "KerraFunctionLibrary.generated.h"


class UKerraAbilitySystemComponent;

UENUM(BlueprintType)
enum class EKerraConfirmType : uint8
{
	Yes,
	No
};

UCLASS()
class KERRA_API UKerraFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// only c++
	static UKerraAbilitySystemComponent* NativeGetKerraASCFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable, Category="Kerra|FunctinLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category="Kerra|FunctinLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	// only c++
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category="Kerra|FunctinLibrary", meta=(DisplayName="Does Actor Have Tag", ExpandEnumAsExecs="OutconfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EKerraConfirmType& OutconfirmType);
};
