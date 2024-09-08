// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KerraHeroAbility.h"
#include "KerraHeroAbility_TagetLock.generated.h"


class UInputMappingContext;
class UKerraWidgetBase;

UCLASS()
class KERRA_API UKerraHeroAbility_TagetLock : public UKerraHeroAbility
{
	GENERATED_BODY()

protected:
	/* Interface */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void OnTaretLockTick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);

private:
	void TryLockOnTarget();
	void GetAvailableActorsToLock();
	void CancelTargetLockAbility();
	void CleanUp();
	AActor* GetNearestTarget(const TArray<AActor*>& InAvailableActors);
	void DrawTargetLockWidget();
	void SetTargetLockWidgetPosition();
	void InitTargetLockMovement();
	void ResetTargetLockMovement();
	void InitTargetLockMappingContext();
	void ResetTargetLockMappingContext();
	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);

private:
	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	float BoxTraceDistance = 500.f;

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	FVector TraceBoxSize = FVector(5000.f, 5000.f, 300.f);

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel ;

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	bool bShowDebugShape = false;

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	TSubclassOf<UKerraWidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	float TargetLockRotInterpSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	float TargetLockMaxWalkSpeed = 200.f;

	UPROPERTY(EditDefaultsOnly, Category="TargetLock")
	TObjectPtr<UInputMappingContext> TargetLockMappingContext;

	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	UPROPERTY()
	AActor* CurrentLockedActor;

	UPROPERTY()
	TObjectPtr<UKerraWidgetBase> DrawnTargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;

	UPROPERTY()
	float CachedDefaultMaxWalkSpeed = 0.f;

	UPROPERTY()
	TObjectPtr<UInputMappingContext> CachedDefaultMappingContext;
};
