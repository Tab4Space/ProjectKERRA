// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraHeroAbility_TagetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/KerraWidgetBase.h"
#include "Player/KerraPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "KerraFunctionLibrary.h"
#include "KerraGameplayTags.h"
#include "Character/KerraHero.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"

void UKerraHeroAbility_TagetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	InitTargetLockMovement();
	InitTargetLockMappingContext();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UKerraHeroAbility_TagetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// cancel ability 이후 알아서 end ability가 호출된다
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();
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
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetAvatarActorFromActorInfo()->GetActorLocation(), CurrentLockedActor->GetActorLocation());

		LookAtRot -= FRotator(TargetLockCameraOffsetDistance, 0.f, 0.f);
		
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
	AvailableActorsToLock.Empty();
	
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
	CachedDefaultMaxWalkSpeed = 0.f;
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

void UKerraHeroAbility_TagetLock::InitTargetLockMovement()
{
	CachedDefaultMaxWalkSpeed = GetKerraPlayerFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;
	GetKerraPlayerFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;
}

void UKerraHeroAbility_TagetLock::ResetTargetLockMovement()
{
	if(CachedDefaultMaxWalkSpeed > 0.f)
	{
		GetKerraPlayerFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
	}
}

void UKerraHeroAbility_TagetLock::InitTargetLockMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetKerraPlayerControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);

	Subsystem->AddMappingContext(TargetLockMappingContext, 3);
}

void UKerraHeroAbility_TagetLock::ResetTargetLockMappingContext()
{
	if(!GetKerraPlayerControllerFromActorInfo())
	{
		return;
	}
	const ULocalPlayer* LocalPlayer = GetKerraPlayerControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);

	Subsystem->RemoveMappingContext(TargetLockMappingContext);
}

void UKerraHeroAbility_TagetLock::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	GetAvailableActorsToLock();

	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	AActor* NewTargetToLock = nullptr;
	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);

	if(InSwitchDirectionTag == KerraGameplayTags::Player_Event_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTarget(ActorsOnLeft);
	}
	else
	{
		NewTargetToLock = GetNearestTarget(ActorsOnRight);
	}

	if(NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}
}

void UKerraHeroAbility_TagetLock::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight)
{
	if(!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	const FVector PlayerLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNorm = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

	for(AActor* AvailableActor : AvailableActorsToLock)
	{
		if(!AvailableActor || AvailableActor == CurrentLockedActor)
		{
			continue;
		}

		const FVector PlayerToAvailableNom = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
		const FVector CrossResult = FVector::CrossProduct(PlayerToCurrentNorm, PlayerToAvailableNom);

		if(CrossResult.Z > 0.f)
		{
			OutActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			OutActorsOnLeft.AddUnique(AvailableActor);
		}
	}
}
