// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KerraPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
