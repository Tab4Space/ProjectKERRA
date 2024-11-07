// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KerraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/Input/KerraInputDataAsset.h"
#include "Component/Input/KerraInputComponent.h"
#include "KerraGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/KerraHero.h"
#include "Component/Quest/KerraQuestComponent.h"


AKerraPlayerController::AKerraPlayerController()
{
	HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId AKerraPlayerController::GetGenericTeamId() const
{
	return HeroTeamID;
}

void AKerraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKerraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"))
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	UKerraInputComponent* KerraInputComponent = CastChecked<UKerraInputComponent>(InputComponent);

	// Movement
	KerraInputComponent->BindNativeInputAction(InputConfigDataAsset, KerraGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AKerraPlayerController::Move);
	KerraInputComponent->BindNativeInputAction(InputConfigDataAsset, KerraGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AKerraPlayerController::LookAt);

	// Targeting
	KerraInputComponent->BindNativeInputAction(InputConfigDataAsset, KerraGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &AKerraPlayerController::Input_SwitchTargetTriggered);
	KerraInputComponent->BindNativeInputAction(InputConfigDataAsset, KerraGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &AKerraPlayerController::Input_SwitchTargetCompleted);

	// Item Pick up
	KerraInputComponent->BindNativeInputAction(InputConfigDataAsset, KerraGameplayTags::InputTag_PickUp, ETriggerEvent::Started, this, &AKerraPlayerController::Input_PickUpStarted);

	// Quest pop-up
	KerraInputComponent->BindNativeInputAction(InputConfigDataAsset, KerraGameplayTags::InputTag_Quest, ETriggerEvent::Started, this, &AKerraPlayerController::Input_Quest);

	// Ability
	KerraInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AKerraPlayerController::AbilityInputPressed, &AKerraPlayerController::AbilityInputReleased);
	
}

void AKerraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}

}

void AKerraPlayerController::LookAt(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
	
}

void AKerraPlayerController::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	// capture switch target lock input
	SwitchDirection = InputActionValue.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("aaaaaaaaaaaa"));
}

void AKerraPlayerController::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	// notify switch target lock input
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(),SwitchDirection.X>0.f? KerraGameplayTags::Player_Event_SwitchTarget_Right : KerraGameplayTags::Player_Event_SwitchTarget_Left,Data);
}

void AKerraPlayerController::Input_PickUpStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), KerraGameplayTags::Player_Event_Consume_Stones, Data);
}

void AKerraPlayerController::Input_Quest(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Quest Input"));
	AKerraHero* ControlledPawn = Cast<AKerraHero>(GetPawn());
	UKerraQuestComponent* QuestComponent = ControlledPawn->GetQuestComponent();

	QuestComponent->ToggleQuestWidget();
	/*
	 * 1. Send
	 */
}


void AKerraPlayerController::AbilityInputPressed(FGameplayTag InInputTag)
{
	GetASC()->OnAbilityInputPressed(InInputTag);
}

void AKerraPlayerController::AbilityInputReleased(FGameplayTag InInputTag)
{
	GetASC()->OnAbilityInputReleased(InInputTag);
}

UKerraAbilitySystemComponent* AKerraPlayerController::GetASC()
{
	if(KerraAbilitySystemComponent == nullptr)
	{
		KerraAbilitySystemComponent = Cast<UKerraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return KerraAbilitySystemComponent;
}
