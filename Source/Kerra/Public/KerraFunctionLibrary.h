// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Struct/KerraEnumTypes.h"
#include "KerraFunctionLibrary.generated.h"


class AKerraHUD;
class UKerraInventoryComponent;
class UKerraQuestComponent;
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

	static UKerraQuestComponent* NativeGetKerraQuestComponentFromActor(AActor* InActor);
	static UKerraInventoryComponent* NativeGetKerraInventoryComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintPure, Category="Kerra|FunctinLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category="Kerra|FunctinLibrary", meta=(CompactNodeTitle="Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category="Kerra|FunctinLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDiffernce);

	UFUNCTION(BlueprintPure, Category="Kerra|FunctinLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category="Kerra|FunctinLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* Instigator, AActor* TargetActor, FGameplayEffectSpecHandle &InSpecHandle);

	UFUNCTION(BlueprintCallable, Category="Kerra|FunctinLibrary",meta=(Latent, WorldContext="WorldContextObject", LatentInfo="LatentInfo", ExpandEnumAsExecs="CountDownInput|CountDownOutput", TotalTime="1.0", UpdateInterval="0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, EKerraCountDownActionInput CountDownInput, UPARAM(DisplayName="Output")EKerraCountDownOutput& CountDownOutput, FLatentActionInfo LatentInfo);

	static AKerraHUD* NativeGetKerraHUD(APlayerController* PC);

	UFUNCTION(BlueprintCallable)
	static AKerraHUD* BP_GetKerraHUD(APlayerController* PC);
};
