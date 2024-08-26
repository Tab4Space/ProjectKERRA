// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/KerraPlayerGameplayAbility.h"
#include "Character/KerraPlayer.h"
#include "Player/KerraPlayerController.h"

AKerraPlayer* UKerraPlayerGameplayAbility::GetKerraPlayerFromActorInfo()
{
	if(!CachedKerraPlayer.IsValid())
	{
		CachedKerraPlayer = Cast<AKerraPlayer>(CurrentActorInfo->AvatarActor);
	}
	return CachedKerraPlayer.IsValid() ? CachedKerraPlayer.Get() : nullptr;
}

AKerraPlayerController* UKerraPlayerGameplayAbility::GetKerraPlayerControllerFromActorInfo()
{
	if(!CachedKerraPlayerController.IsValid())
	{
		CachedKerraPlayerController = Cast<AKerraPlayerController>(CurrentActorInfo->AvatarActor);
	}
	return CachedKerraPlayerController.IsValid() ? CachedKerraPlayerController.Get() : nullptr;
}

UKerraPlayerCombatComponent* UKerraPlayerGameplayAbility::GetKerraPlayerCombatComponentFromActorInfo()
{
	return GetKerraPlayerFromActorInfo()->GetKerraPlayerCombatComponent();
}
