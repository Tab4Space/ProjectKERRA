// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KerraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/KerraInputConfig.h"
#include "Component/Input/KerraInputComponent.h"
#include "KerraGameplayTags.h"


AKerraPlayerController::AKerraPlayerController()
{
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

	KerraInputComponent->BindNativeInputAction(InputConfigDataAsset, KerraGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AKerraPlayerController::Move);
	KerraInputComponent->BindNativeInputAction(InputConfigDataAsset, KerraGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AKerraPlayerController::LookAt);
	
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
