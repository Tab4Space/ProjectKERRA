// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/Weapon/KerraWeaponBase.h"
#include "Struct/KerraStructTypes.h"
#include "PlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class KERRA_API APlayerWeapon : public AKerraWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	FKerraPlayerWeaponData KerraPlayerWeaponData;
	
	
};
