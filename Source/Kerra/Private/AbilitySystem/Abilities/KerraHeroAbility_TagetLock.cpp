// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraHeroAbility_TagetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/KerraWidgetBase.h"
#include "Player/KerraPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "KerraFunctionLibrary.h"
#include "KerraGameplayTags.h"
#include "Character/KerraHero.h"
#include "Kismet/KismetMathLibrary.h"

void UKerraHeroAbility_TagetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UKerraHeroAbility_TagetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// cancel ability 이후 알아서 end ability가 호출된다
	CleanUp();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UKerraHeroAbility_TagetLock::OnTaretLockTick(float DeltaTime)
{
	// This function actually run important logic
	if(!CurrentLockedActor ||
		UKerraFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor, KerraGameplayTags::Shared_Status_Dead) ||
		UKerraFunctionLibrary::NativeDoesActorHaveTag(GetAvatarActorFromActorInfo(), KerraGameplayTags::Shared_Status_Dead))
	{
		CancelTargetLockAbility();
		return;
	}
	SetTargetLockWidgetPosition();

	const bool bShouldOverrideRotation = \
	!UKerraFunctionLibrary::NativeDoesActorHaveTag(GetAvatarActorFromActorInfo(), KerraGameplayTags::Player_Status_Rolling) && \
	!UKerraFunctionLibrary::NativeDoesActorHaveTag(GetAvatarActorFromActorInfo(), KerraGameplayTags::Player_Status_Blocking);

	if(bShouldOverrideRotation)
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetAvatarActorFromActorInfo()->GetActorLocation(), CurrentLockedActor->GetActorLocation());
		const FRotator CurrentControlRot = GetKerraPlayerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotInterpSpeed);

		GetKerraPlayerControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		GetAvatarActorFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	}
}

void UKerraHeroAbility_TagetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();
	if(AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	CurrentLockedActor = GetNearestTarget(AvailableActorsToLock);
	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else
	{
		CancelTargetLockAbility();
	}
	
}

void UKerraHeroAbility_TagetLock::GetAvailableActorsToLock()
{
	TArray<FHitResult> BoxTraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetAvatarActorFromActorInfo(),
		GetAvatarActorFromActorInfo()->GetActorLocation(),
		GetAvatarActorFromActorInfo()->GetActorLocation() + GetAvatarActorFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		GetAvatarActorFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowDebugShape? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for( const FHitResult& TraceHit : BoxTraceHits)
	{
		if(AActor* HitActor = TraceHit.GetActor())
		{
			if(HitActor != GetAvatarActorFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

void UKerraHeroAbility_TagetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UKerraHeroAbility_TagetLock::CleanUp()
{
	AvailableActorsToLock.Empty();
	CurrentLockedActor = nullptr;
	if(DrawnTargetLockWidget)
	{
		DrawnTargetLockWidget->RemoveFromParent();
	}
	DrawnTargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
}

AActor* UKerraHeroAbility_TagetLock::GetNearestTarget(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetAvatarActorFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}

void UKerraHeroAbility_TagetLock::DrawTargetLockWidget()
{
	if(!DrawnTargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Not assign valid widget class"));
		DrawnTargetLockWidget = CreateWidget<UKerraWidgetBase>(GetKerraPlayerControllerFromActorInfo(), TargetLockWidgetClass);

		check(DrawnTargetLockWidget)
		DrawnTargetLockWidget->AddToViewport();	
	}
}

void UKerraHeroAbility_TagetLock::SetTargetLockWidgetPosition()
{
	if(!DrawnTargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetKerraPlayerControllerFromActorInfo(), CurrentLockedActor->GetActorLocation(), ScreenPosition, true);

	if(TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		// fill in static function or lambda function
		DrawnTargetLockWidget->WidgetTree->ForEachWidget([this](UWidget* FoundWidget)
		{
			if(USizeBox* SizeBox = Cast<USizeBox>(FoundWidget))
			{
				TargetLockWidgetSize.X = SizeBox->GetWidthOverride();
				TargetLockWidgetSize.Y = SizeBox->GetHeightOverride();
			}
		});
	}
	ScreenPosition -= (TargetLockWidgetSize / 2.f);
	
	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}
