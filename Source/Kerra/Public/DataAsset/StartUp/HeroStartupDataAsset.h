// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUp/KerraStartUpDataAssetBase.h"
#include "Struct/KerraStructTypes.h"
#include "HeroStartupDataAsset.generated.h"


UCLASS()
class KERRA_API UHeroStartupDataAsset : public UKerraStartUpDataAssetBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UKerraAbilitySystemComponent* InASC, int32 InApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="StartupData", meta=(TitleProperty="InputTag"))
	TArray<FKerraPlayerAbilitySet> KerraPlayerStartupAbilitySets;
};

