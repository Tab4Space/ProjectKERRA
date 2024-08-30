// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KerraEnemy.h"
#include "AbilitySystem/KerraAbilitySystemComponent.h"
#include "AbilitySystem/KerraAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/Combat/KerraEnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAsset/EnemyStartupDataAsset.h"


AKerraEnemy::AKerraEnemy()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	AbilitySystemComponent = CreateDefaultSubobject<UKerraAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UKerraAttributeSet>("AttributeSet");
	
	EnemyCombatComponent = CreateDefaultSubobject<UKerraEnemyCombatComponent>("EnemyCombatComponent");
	
}

void AKerraEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

UKerraCombatComponent* AKerraEnemy::GetKerraCombatComponent() const
{
	return EnemyCombatComponent;
}

void AKerraEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilityActorInfo();
	InitStartupData();
}

void AKerraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
}

void AKerraEnemy::InitStartupData()
{
	if(CharacterStartupData.IsNull())
	{
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if(UStartupDataAssetBase* LoadedData = CharacterStartupData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(Cast<UKerraAbilitySystemComponent>(AbilitySystemComponent));
					UE_LOG(LogTemp, Warning, TEXT("Complete loading %s"), *CharacterStartupData.ToSoftObjectPath().ToString());
				}
			}
		)
	);
}
