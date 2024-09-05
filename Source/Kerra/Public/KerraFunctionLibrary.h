// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Struct/KerraEnumTypes.h"
#include "KerraFunctionLibrary.generated.h"


struct FScalableFloat;
class UKerraAbilitySystemComponent;
class UKerraCombatComponent;

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

	UFUNCTION(BlueprintCallable, Category="Kerra|FunctinLibrary", meta=(DisplayName="Does Actor Have Tag", ExpandEnumAsExecs="OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EKerraConfirmType& OutConfirmType);

	static UKerraCombatComponent* NativeGetKerraCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="Kerra|FunctinLibrary", meta=(DisplayName="Get Kerra Combat Component From Actor", ExpandEnumAsExecs="OutValidType"))
	static UKerraCombatComponent* BP_GetKerraCombatComponentFromActor(AActor* InActor, EKerraValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category="Kerra|FunctinLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category="Kerra|FunctinLibrary", meta=(CompactNodeTitle="Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);
		
};
