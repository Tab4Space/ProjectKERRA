// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "Component/Combat/KerraCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "KerraFunctionLibrary.h"
#include "KerraGameplayTags.h"

void UKerraGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	/* If activation policy is OnGiven then TryActivateAbility */
	if(AbilityActivationPolicy == EKerraAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UKerraGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(AbilityActivationPolicy == EKerraAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UKerraCombatComponent* UKerraGameplayAbility::GetKerraCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UKerraCombatComponent>();
}

UKerraAbilitySystemComponent* UKerraGameplayAbility::GetKerraAbilitySystemComponentFromActorInfo() const
{
	return Cast<UKerraAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UKerraGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(TargetASC && InSpecHandle.IsValid());
	
	return GetKerraAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UKerraGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EKerraSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);
	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EKerraSuccessType::Successful : EKerraSuccessType::Fail;
	return ActiveGameplayEffectHandle;
}

void UKerraGameplayAbility::ApplyGameplaySpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle, const TArray<FHitResult>& HitResults)
{
	if(HitResults.IsEmpty())
	{
		return;
	}

	APawn* OwningPawn = Cast<APawn>(GetAvatarActorFromActorInfo());
	TArray<APawn*> UniqueHitPawns;
	for(const FHitResult& Hit : HitResults)
	{
		if(APawn* HitPawn = Cast<APawn>(Hit.GetActor()))
		{
			UniqueHitPawns.AddUnique(HitPawn);
		}
	}

	for(APawn* HitPawn : UniqueHitPawns)
	{
		if(UKerraFunctionLibrary::IsTargetPawnHostile(OwningPawn, HitPawn))
		{
			FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(HitPawn, InSpecHandle);
			FGameplayEventData Data;
			Data.Instigator = OwningPawn;
			Data.Target = HitPawn;
			if(ActiveGameplayEffectHandle.WasSuccessfullyApplied())
			{
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitPawn, KerraGameplayTags::Shared_Event_HitReact, Data);
			}
		}
	}
}
