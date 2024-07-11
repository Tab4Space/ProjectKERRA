// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KerraPlayerController.h"

#include "EnhancedInputSubsystems.h"

AKerraPlayerController::AKerraPlayerController()
{
}

void AKerraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(KerraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(KerraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
	
}
