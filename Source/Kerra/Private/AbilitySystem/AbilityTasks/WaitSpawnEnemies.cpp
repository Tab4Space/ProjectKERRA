// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/WaitSpawnEnemies.h"
#include "AbilitySystemComponent.h"
#include "Engine/AssetManager.h"
#include "Character/KerraEnemy.h"
#include "NavigationSystem.h"

UWaitSpawnEnemies* UWaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag, TSoftClassPtr<AKerraEnemy> SoftEnemyClassToSpawn, int32 NumToSpawn, const FVector& SpawnOrigin, float RandomSpawnRadius)
{
	UWaitSpawnEnemies* Node = NewAbilityTask<UWaitSpawnEnemies>(OwningAbility);
	Node->CachedEventTag = EventTag;
	Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
	Node->CachedNumToSpawn = NumToSpawn;
	Node->CachedSpawnOrigin = SpawnOrigin;
	Node->CachedRandomSpawnRadius = RandomSpawnRadius;
	
	return Node;
}

void UWaitSpawnEnemies::Activate()
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	DelegateHandle = Delegate.AddUObject(this, &UWaitSpawnEnemies::OnGameplayEventReceived);
}

void UWaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	Delegate.Remove(DelegateHandle);
	Super::OnDestroy(bInOwnerFinished);
}

void UWaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* InPayload)
{
	if(ensure(!CachedSoftEnemyClassToSpawn.IsNull()))
	{
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(CachedSoftEnemyClassToSpawn.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UWaitSpawnEnemies::OnEnemyClassLoaded));	
	}
	else
	{
		if(ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(TArray<AKerraEnemy*>());
		}
		EndTask();
	}
}
void UWaitSpawnEnemies::OnEnemyClassLoaded()
{
	// Actually spawn
	UClass* LoadedClass = CachedSoftEnemyClassToSpawn.Get();
	UWorld* World = GetWorld();

	if(!LoadedClass || !World)
	{
		if(ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(TArray<AKerraEnemy*>());
		}
		EndTask();
		return;
	}

	TArray<AKerraEnemy*> SpawnedEnemies;
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	for(int32 i=0; i < CachedNumToSpawn; i++)
	{
		FVector RandomLocation;
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, CachedSpawnOrigin, RandomLocation,CachedRandomSpawnRadius);

		RandomLocation += FVector(0.f, 0.f, 150.f);

		const FRotator SpawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

		AKerraEnemy* SpawnedEnemy = World->SpawnActor<AKerraEnemy>(LoadedClass, RandomLocation, SpawnFacingRotation, SpawnParam);

		if(SpawnedEnemy)
		{
			SpawnedEnemies.Add(SpawnedEnemy);
		}
	}

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		if(!SpawnedEnemies.IsEmpty())
		{
			OnSpawnFinished.Broadcast(SpawnedEnemies);
		}
		else
		{
			DidNotSpawn.Broadcast(TArray<AKerraEnemy*>());
		}
	}
	EndTask();
}

