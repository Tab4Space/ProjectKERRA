// Fill out your copyright notice in the Description page of Project Settings.


#include "KerraFunctionLibrary.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Interface/KerraCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "KerraGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"

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

void UKerraFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EKerraConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EKerraConfirmType::Yes : EKerraConfirmType::No; 
}

UKerraCombatComponent* UKerraFunctionLibrary::NativeGetKerraCombatComponentFromActor(AActor* InActor)
{
	check(InActor)

	if(IKerraCombatInterface* CombatInterface = Cast<IKerraCombatInterface>(InActor))
	{
		return CombatInterface->GetKerraCombatComponent();
	}
	return nullptr;
}

UKerraCombatComponent* UKerraFunctionLibrary::BP_GetKerraCombatComponentFromActor(AActor* InActor, EKerraValidType& OutValidType)
{
	UKerraCombatComponent* CombatComponent = NativeGetKerraCombatComponentFromActor(InActor);
	OutValidType = CombatComponent ? EKerraValidType::Valid : EKerraValidType::Invalid;
	return CombatComponent;
}

bool UKerraFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if(QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

float UKerraFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UKerraFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDiffernce)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNorm = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNorm);
	OutAngleDiffernce = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNorm);
	if(CrossResult.Z < 0.f)
	{
		OutAngleDiffernce *= -1.f;
	}

	if(OutAngleDiffernce >= -45.f && OutAngleDiffernce <= 45.f)
	{
		return KerraGameplayTags::Shared_Status_HitReact_Front;
	}
	else if(OutAngleDiffernce < -45.f && OutAngleDiffernce > -135.f)
	{
		return KerraGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDiffernce < -135.f || OutAngleDiffernce >135.f)
	{
		return KerraGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDiffernce > 45.f && OutAngleDiffernce <= 135.f)
	{
		return KerraGameplayTags::Shared_Status_HitReact_Right;
	}

	return KerraGameplayTags::Shared_Status_HitReact_Front;
}

bool UKerraFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	// check valid block direction
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());
	return DotResult < -0.1f;
}

bool UKerraFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* Instigator, AActor* TargetActor, FGameplayEffectSpecHandle& InSpecHandle)
{
	UKerraAbilitySystemComponent* SourceASC = NativeGetKerraASCFromActor(Instigator);
	UKerraAbilitySystemComponent* TargetASC = NativeGetKerraASCFromActor(TargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

