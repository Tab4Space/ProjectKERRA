// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KerraPlayer.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DataAsset/StartupDataAssetBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/KerraPlayerState.h"
#include "Component/Combat/KerraPlayerCombatComponent.h"

AKerraPlayer::AKerraPlayer()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	PlayerCombatComponent = CreateDefaultSubobject<UKerraPlayerCombatComponent>("PlayerCombatComp");
	
}

void AKerraPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();					// Set owner and avatar in server side

	if(!CharacterStartupData.IsNull())
	{
		if(UStartupDataAssetBase* LoadedData = CharacterStartupData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(Cast<UKerraAbilitySystemComponent>(AbilitySystemComponent));
		}
	}
}

void AKerraPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();					// Set owner and avatar in client side
	
}

void AKerraPlayer::InitAbilityActorInfo()
{
	AKerraPlayerState* KerraPlayerState = GetPlayerState<AKerraPlayerState>();
	checkf(KerraPlayerState, TEXT("Not valid player state"));

	KerraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(KerraPlayerState, this);
	AbilitySystemComponent = KerraPlayerState->GetAbilitySystemComponent();

	AttributeSet = KerraPlayerState->GetAttributeSet();
}
