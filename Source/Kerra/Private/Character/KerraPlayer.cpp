// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KerraPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/KerraPlayerState.h"

AKerraPlayer::AKerraPlayer()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	
}

UAbilitySystemComponent* AKerraPlayer::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AKerraPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UE_LOG(LogTemp, Warning, TEXT("PossessedBy"));
	AKerraPlayerState* KerraPlayerState = GetPlayerState<AKerraPlayerState>();
	check(KerraPlayerState);
	AbilitySystemComponent = KerraPlayerState->GetAbilitySystemComponent();
	
}
