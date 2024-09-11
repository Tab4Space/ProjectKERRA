// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "WaitSpawnEnemies.generated.h"


class AKerraEnemy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemiesDelegate, const TArray<AKerraEnemy*>&, SpawnedEnemies);

UCLASS()
class KERRA_API UWaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Kerra|AbilityTasks", meta=(DisplayName="Wait Gameplay Event And Spawn Enemies", HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly="true", NumtoSpawn="1", RandomSpawnRadius="200"))
	static UWaitSpawnEnemies* WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag, TSoftClassPtr<AKerraEnemy> SoftEnemyClassToSpawn, int32 NumToSpawn, const FVector& SpawnOrigin, float RandomSpawnRadius);

	/* UGameplayTask Interface */
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	void OnGameplayEventReceived(const FGameplayEventData* InPayload);
	void OnEnemyClassLoaded();
	
public:
	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate OnSpawnFinished;

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate DidNotSpawn;

private:
	FGameplayTag CachedEventTag;
	TSoftClassPtr<AKerraEnemy> CachedSoftEnemyClassToSpawn;
	int32 CachedNumToSpawn;
	FVector CachedSpawnOrigin;
	float CachedRandomSpawnRadius;
	FDelegateHandle DelegateHandle;
};
